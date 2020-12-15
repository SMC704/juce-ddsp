/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "HarmonicEditor.h"
#include "codegen/additive.h"
#include "codegen/subtractive.h"
#include "codegen/getPitch.h"
#include "codegen/compute_loudness.h"
#include "codegen/scale_f0.h"
#include "TensorflowHandler.h"


// ........ don't ask
FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
    return _iob;
}

extern "C" int __cdecl __ms_vsnprintf(char* s, size_t n, const char* format, va_list arg)
{
    //return printf(s, n, format, arg);
    printf(s, format);
    return 0;
}

//==============================================================================
DdspsynthAudioProcessor::DdspsynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::mono(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),

#endif
    : forwardFFT(fftOrder),
    parameters(*this, nullptr, juce::Identifier("DDSPSynth"),
        {
            // Input
           std::make_unique<juce::AudioParameterBool>("inputIsLine", "Input is line in", false),
           // Model
           std::make_unique<juce::AudioParameterBool>("modelOn", "Use model", false),
           std::make_unique<juce::AudioParameterChoice>("modelSelect", "Model select", juce::StringArray({ "violin", "flute", "tenorsax", "trumpet" }), 0),
           // Additive
           std::make_unique<juce::AudioParameterBool>("additiveOn", "Additive synth on", true),
           std::make_unique<juce::AudioParameterFloat>("additiveShift", "Shift amount", -12.0f, 12.0f, 0.0f),
           std::make_unique<juce::AudioParameterFloat>("additiveStretch", "Stretch amount", -1.0f, 1.0f, 0.0f),
           std::make_unique<juce::AudioParameterFloat>("additiveGain", "Additive gain", -60.0f, 0.0f, 0.0f),
           // Subtractive
           std::make_unique<juce::AudioParameterBool>("noiseOn", "Noise synth on", true),
           std::make_unique<juce::AudioParameterFloat>("noiseColor", "Noise color", -1.0f, 1.0f, 0.0f),
           std::make_unique<juce::AudioParameterFloat>("noiseGain", "Noise gain", -60.0f, 0.0f, 0.0f),
           // Modulation
           std::make_unique<juce::AudioParameterBool>("modulationOn", "Modulation on", false),
           std::make_unique<juce::AudioParameterFloat>("modulationRate", "Rate", 0.0f, 10.0f, 1.0f),
           std::make_unique<juce::AudioParameterFloat>("modulationDelay", "Delay", 0.01f, 0.5f, 0.03f),
           std::make_unique<juce::AudioParameterFloat>("modulationAmount", "Amount", 0.0f, 100.0f, 50.0f),
           // Reverb
           std::make_unique<juce::AudioParameterBool>("reverbOn", "Reverb on", false),
           std::make_unique<juce::AudioParameterFloat>("reverbMix", "Mix", 0.0f, 10.0f, 1.0f),
           std::make_unique<juce::AudioParameterFloat>("reverbSize", "Size", 0.10f, 2.0f, 1.0f),
           std::make_unique<juce::AudioParameterFloat>("reverbGlow", "Glow", 0.0f, 100.0f, 0.0f),
           // Output
           std::make_unique<juce::AudioParameterFloat>("outputGain", "Output gain", -60.0f, 0.0f, -6.0f),
           // Midi
           std::make_unique<juce::AudioParameterFloat>("attack", "Attack", 0.0f, 2.0f, 0.1f),
           std::make_unique<juce::AudioParameterFloat>("decay", "Decay", 0.0f, 2.0f, 0.1f),
           std::make_unique<juce::AudioParameterFloat>("sustain", "Sustain", 0.0f, 1.0f, 0.1f),
           std::make_unique<juce::AudioParameterFloat>("release", "Release", 0.0f, 2.0f, 0.1f),
        })/*,
        tfHandler(*this)*/
{
    modelDir = juce::File::getSpecialLocation(juce::File::SpecialLocationType::currentApplicationFile).getParentDirectory().getChildFile("Models");
    jassert(modelDir.exists()); // Check that the Models folder exists in the same path as the plugin

    inputSelectParameter = parameters.getRawParameterValue("inputIsLine");
    modelOnParameter = parameters.getRawParameterValue("modelOn");
    modelChoiceParameter = parameters.getRawParameterValue("modelSelect");
    additiveOnParameter = parameters.getRawParameterValue("additiveOn");
    additiveShiftParameter = parameters.getRawParameterValue("additiveShift");
    additiveStretchParameter = parameters.getRawParameterValue("additiveStretch");
    additiveGainParameter = parameters.getRawParameterValue("additiveGain");
    noiseOnParameter = parameters.getRawParameterValue("noiseOn");
    noiseColorParameter = parameters.getRawParameterValue("noiseColor");
    noiseGainParameter = parameters.getRawParameterValue("noiseGain");
    modulationOnParameter = parameters.getRawParameterValue("modulationOn");
    modulationRateParameter = parameters.getRawParameterValue("modulationRate");
    modulationDelayParameter = parameters.getRawParameterValue("modulationDelay");
    modulationAmountParameter = parameters.getRawParameterValue("modulationAmount");
    reverbOnParameter = parameters.getRawParameterValue("reverbOn");
    reverbMixParameter = parameters.getRawParameterValue("reverbMix");
    reverbSizeParameter = parameters.getRawParameterValue("reverbSize");
    reverbGlowParameter = parameters.getRawParameterValue("reverbGlow");
    outputGainParameter = parameters.getRawParameterValue("outputGain");
    attackParameter = parameters.getRawParameterValue("attack");
    decayParameter = parameters.getRawParameterValue("decay");
    sustainParameter = parameters.getRawParameterValue("sustain");
    releaseParameter = parameters.getRawParameterValue("release");

    parameters.addParameterListener("modelSelect", this);

    for (int i = 0; i < 65; i++) {
        magnitudes[i] = 6;
    }
    for (int i = 0; i < 4096; i++) {
        amplitudes[i] = 0;
        f0[i] = 0;
    }
    for (int i = 0; i < max_n_harmonics; i++) {
        harmonics[i] = 0.0;
    }

    tf_amps = -120;
    tf_f0 = 0;
}

DdspsynthAudioProcessor::~DdspsynthAudioProcessor()
{
    tfHandler.stopThread(100);
}

//==============================================================================
const juce::String DdspsynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DdspsynthAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool DdspsynthAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool DdspsynthAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double DdspsynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DdspsynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DdspsynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DdspsynthAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String DdspsynthAudioProcessor::getProgramName(int index)
{
    return {};
}

void DdspsynthAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void DdspsynthAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    tfHandler.setAsyncUpdater(this);
    auto param = (juce::AudioParameterChoice*) parameters.getParameter("modelSelect");
    juce::String modelName = param->getCurrentChoiceName();
    juce::String modelPath = modelDir.getChildFile(modelName).getFullPathName();
    parseModelConfigJSON(modelPath);
    tfHandler.loadModel(modelPath.getCharPointer());

    adsr.setSampleRate(sampleRate);
    adsr.setParameters(adsrParams);
    adsr.reset();

    abHandler.prepare("yinfft", 4096, samplesPerBlock, (uint_t)sampleRate);
    abHandler.setTolerance(0.8);

    abHandler.setSilence(-50);
}

void DdspsynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    abHandler.releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DdspsynthAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   //#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
    //#endif

    return true;
#endif
}
#endif

void DdspsynthAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    shouldSynthesize = true;
    const float* in_l = buffer.getReadPointer(0);
    numSamples = buffer.getNumSamples();
    if (*inputSelectParameter) //Input is line-in
    {
        AubioHandler::AubioResults aubioResults = abHandler.process(buffer);
        double mlInput[4096];
        for (int i = 0; i < 4096; i++)
        {
            if (i < numSamples)
                mlInput[i] = in_l[i];
            else
                mlInput[i] = 0;
        }

        //tf_amps = compute_loudness((double)numSamples, mlInput, getSampleRate());
        tf_amps = aubioResults.loudness;
        DBG(aubioResults.confidence);
        f0_in = aubioResults.pitch;
        tf_f0 = f0_in;
        for (int i = 0; i < 4096; i++)
        {
            f0[i] = f0_in;
        }
    }
    else //Input is midi
    {
        buffer.clear();
        adsrParams = { *attackParameter, *decayParameter, *sustainParameter, *releaseParameter };
        adsr.setParameters(adsrParams);
        int time;
        juce::MidiMessage m;
        for (juce::MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
        {
            if (m.isNoteOn())
            {
                adsr.reset();
                adsr.noteOn();
                midiVelocity = m.getFloatVelocity();
                currentMidiNote = m.getNoteNumber();
                midiNoteHz = m.getMidiNoteInHertz(currentMidiNote);
                tf_amps = -120;
                tf_f0 = midiNoteHz;
            }
            else if (m.isNoteOff())
            {
                if (m.getNoteNumber() == currentMidiNote)
                    adsr.noteOff();
            }
        }
        if (!adsr.isActive()) 
            shouldSynthesize = false;

        tf_f0 = midiNoteHz;
        tf_amps = log10(juce::jmax(midiVelocity * adsrVelocity, 0.000001f)) * 20.0f;
        for (int i = 0; i < numSamples && adsr.isActive(); i++)
        {
            f0[i] = midiNoteHz;
            adsrVelocity = adsr.getNextSample();
        }
    }


    if (*modelOnParameter) {
        if (!tfHandler.isThreadRunning())
        {
            tfHandler.setInputs(tf_f0, tf_amps);
            tfHandler.startThread();
        }
    }

    double harms_copy[max_n_harmonics];
    double mags_copy[65];
    double amps_copy[4096];
    for (int i = 0; i < n_harmonics; i++) {
        if (*modelOnParameter)
            harms_copy[i] = harmonics[i] * userHarmonics[i] * 2;
        else
            harms_copy[i] = 10 * (1 - userHarmonics[i]) - 5;
    }
    for (int i = 0; i < 65; i++) {
        mags_copy[i] = magnitudes[i];
    }
    for (int i = 0; i < 4096; i++) {
        if (*modelOnParameter)
            amps_copy[i] = amplitudes[i];
        else
            amps_copy[i] = midiVelocity * adsrVelocity;
    }

    if (*additiveOnParameter && shouldSynthesize) {
        additive((double)numSamples, getSampleRate(), amps_copy, n_harmonics, harms_copy, f0, phaseBuffer_in, (double)*additiveShiftParameter, (double)*additiveStretchParameter, addBuffer, phaseBuffer_out);
    }
    else {
        for (int i = 0; i < 4096; i++)
        {
            addBuffer[i] = 0;
        }
    }


    if (*noiseOnParameter && shouldSynthesize)
    {
        subtractive(numSamples, mags_copy, (double)*noiseColorParameter, initial_bias, subBuffer);
    }
    else {
        for (int i = 0; i < 4096; i++)
        {
            subBuffer[i] = 0;
        }
    }
    for (int i = 0; i < max_n_harmonics; ++i) {
        phaseBuffer_in[i] = phaseBuffer_out[i];
    }

    auto outL = buffer.getWritePointer(0);
    auto outR = buffer.getWritePointer(1);

    for (int i = 0; i < buffer.getNumSamples(); i++) {
        float additiveGain = pow(10.0f, (*additiveGainParameter / 20));
        float noiseGain = pow(10.0f, (*noiseGainParameter / 20));
        float outGain = pow(10.0f, (*outputGainParameter / 20));

        if (!(*modelOnParameter)) // workaround to prevent MIDI-related hearing damage
            outGain *= 0.02;

        float out = (addBuffer[i] * additiveGain + subBuffer[i] * noiseGain) * outGain;
        pushNextSampleIntoFifo(out);
        outL[i] = out;
        outR[i] = out;
    }
}

void DdspsynthAudioProcessor::parseModelConfigJSON(juce::String path)
{
    // Parses config.json for model selected. Sets default values if file isn't found.
    juce::File config_file = juce::File(path + "/config.json");
    jassert(config_file.existsAsFile());
    juce::var config = juce::JSON::parse(config_file);
    n_harmonics = config.getProperty("n_harmonics", 50);
    initial_bias = config.getProperty("initial_bias", -5.0f);
    if(config.hasProperty("attack"))
        *attackParameter = config.getProperty("attack", juce::var(*attackParameter));
    if (config.hasProperty("decay"))
        *decayParameter = config.getProperty("decay", juce::var(*decayParameter));
    if (config.hasProperty("sustain"))
        *sustainParameter = config.getProperty("sustain", juce::var(*sustainParameter));
    if (config.hasProperty("release"))
        *releaseParameter = config.getProperty("release", juce::var(*releaseParameter));
}

void DdspsynthAudioProcessor::setModelOutput(TensorflowHandler::ModelResults tfResults)
{
    for (int i = 0; i < n_harmonics; i++) {
        harmonics[i] = tfResults.harmonicDistribution[i];
    }
    for (int i = 0; i < 65; i++) {
        magnitudes[i] = tfResults.noiseMagnitudes[i];
    }
    for (int i = 0; i < numSamples; i++) {
        amplitudes[i] = (double)tfResults.amplitudes[0] + 1.0f;
    }
}

void DdspsynthAudioProcessor::onHarmonicsChange(double* newHarmonics, int nHarmonics)
{
    for (int i = 0; i < nHarmonics && i < n_harmonics; i++) {
        userHarmonics[i] = newHarmonics[i];
    }
}

int DdspsynthAudioProcessor::getNumberOfHarmonics()
{
    return n_harmonics;
}

void DdspsynthAudioProcessor::parameterChanged(const juce::String & parameterID, float newValue)
{
    if (parameterID == "modelSelect")
    {
        // getRawParameterValue is "not guaranteed" to contain up-to-date value
        auto param = (juce::AudioParameterChoice*) parameters.getParameter("modelSelect");
        juce::String modelName = param->getCurrentChoiceName();
        DBG("Processor notified to select model " + modelName);
        juce::String modelPath = modelDir.getChildFile(modelName).getFullPathName();
        if (modelDir.getChildFile(modelName).exists()) 
        {
            parseModelConfigJSON(modelPath);
            tfHandler.loadModel(modelPath.getCharPointer());
        }
        else
        {
            juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::WarningIcon, "Model not found!", "The plugin expected to find the " + modelName + " model in this path:\n" + modelPath);
        }
    }
}

void DdspsynthAudioProcessor::handleAsyncUpdate()
{
    setModelOutput(tfHandler.getOutputs());
}


//==============================================================================
bool DdspsynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DdspsynthAudioProcessor::createEditor()
{
    return new DdspsynthAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void DdspsynthAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DdspsynthAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DdspsynthAudioProcessor();
}

//===============================================================================
// Spectrogram methods

void DdspsynthAudioProcessor::pushNextSampleIntoFifo(float sample) noexcept
{
    // if the fifo contains enough data, set a flag to say
    // that the next line should now be rendered..
    if (fifoIndex == fftSize)
    {
        if (!nextFFTBlockReady)
        {
            juce::zeromem(fftData, sizeof(fftData));
            memcpy(fftData, fifo, sizeof(fifo));
            nextFFTBlockReady = true;
        }

        fifoIndex = 0;
    }

    fifo[fifoIndex++] = sample;
}
