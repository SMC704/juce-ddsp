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
        std::make_unique<juce::AudioParameterBool>("modelOn", "Use model", true),
        std::make_unique<juce::AudioParameterChoice>("modelSelect", "Model select", juce::StringArray({ "Violin", "Flute", "TenorSax", "Trumpet" }), 0),
        // Additive
        std::make_unique<juce::AudioParameterBool>("additiveOn", "Additive synth on", true),
        std::make_unique<juce::AudioParameterFloat>("additiveShift", "Shift amount", -12.0f, 12.0f, 0.0f),
        std::make_unique<juce::AudioParameterFloat>("additiveStretch", "Stretch amount", -1.0f, 1.0f, 0.0f),
        std::make_unique<juce::AudioParameterFloat>("additiveGain", "Additive gain", -60.0f, 0.0f, -6.0f),
        // Subtractive
        std::make_unique<juce::AudioParameterBool>("noiseOn", "Noise synth on", true),
        std::make_unique<juce::AudioParameterFloat>("noiseColor", "Noise color", -1.0f, 1.0f, 0.0f),
        std::make_unique<juce::AudioParameterFloat>("noiseGain", "Noise gain", -60.0f, 0.0f, -6.0f),
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
    })/*, 
    tfHandler(*this)*/
{
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

    for (int i = 0; i < 65; i++) {
        magnitudes[i] = 0;
    }
    for (int i = 0; i < 4096; i++) {
        amplitudes[i] = 0;
        f0[i] = 0;
    }
    for (int i = 0; i < 50; i++) {
        harmonics[i] = 0.0;
    }
    for (int i = 0; i < 100; i++)
    {
        tf_amps[i] = -200;
        tf_f0[i] = 0;
    }
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

void DdspsynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DdspsynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void DdspsynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DdspsynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    tfHandler.setAsyncUpdater(this);
    tfHandler.loadModel("C:\\Users\\svkly\\Documents\\SMC\\models-new");
}

void DdspsynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DdspsynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
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

void DdspsynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    const float* in_l = buffer.getReadPointer(0);
    numSamples = buffer.getNumSamples();
    if (*inputSelectParameter) //Input is line-in
    {
        double input[4096];
        for (int i = 0; i < 4096; i++)
        {
            if (i < numSamples)
                input[i] = in_l[i];
            else
                input[i] = 0;
        }

        double f0_from_pitch = getPitch((double)numSamples, input, getSampleRate());
        compute_loudness((double)numSamples, input, getSampleRate(), ld);
        for (int i = 0; i < 100; i++)
        {
            tf_amps[i] = ld[i] /*/ 120.0f + 1.0f*/; // ddsp.training.preprocessing.py line 77
            f0_in[i] = f0_from_pitch;
        }

        scale_f0(f0_in, true, f0_out);

        for (int i = 0; i < 100; i++)
        {
            tf_f0[i] = (float)f0_out[i];
        }
        for (int i = 0; i < 4096; i++)
        {
            if (f0_from_pitch != -1)
                f0[i] = f0_from_pitch;
            else
                f0[i] = 0;
        }
    }
    else //Input is midi
    {
        buffer.clear();
        int time;
        juce::MidiMessage m;
        for (juce::MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
        {
            if (m.isNoteOn())
            {
                float vel = m.getFloatVelocity();
                vel = log10f(vel) * 20.0f /*/ 120.0f + 1.0f*/; // ddsp.training.preprocessing.py line 77;
                int note = m.getNoteNumber();
                double noteHz = m.getMidiNoteInHertz(note);
                float midi_ranged = note /*/ 127.0f*/; // ddsp.training.preprocessing.py line 76
                for (int i = 0; i < 1024; i++)
                {
                    tf_amps[i] = vel;
                    tf_f0[i] = noteHz/*midi_ranged*/;
                }
                for (int i = 0; i < 4096; i++)
                {
                    f0[i] = noteHz;
                }

            }
            else if (m.isNoteOff())
            {
                for (int i = 0; i < 1024; i++)
                {
                    tf_amps[i] = -200;
                    tf_f0[i] = 0;
                }
                for (int i = 0; i < 4096; i++)
                {
                    f0[i] = 0;
                }
            }
        }
    }

    if (!tfHandler.isThreadRunning())
    {
        tfHandler.setInputs(tf_f0, tf_amps);
        tfHandler.startThread();
    }

    double harms_copy[60];
    double mags_copy[65];
    double amps_copy[4096];
    for (int i = 0; i < 50; i++) {
        harms_copy[i] = harmonics[i];
    }
    for (int i = 0; i < 65; i++) {
        mags_copy[i] = magnitudes[i];
    }
    for (int i = 0; i < 4096; i++) {
        amps_copy[i] = amplitudes[i];
    }

    if (*additiveOnParameter) {
        additive((double)numSamples, getSampleRate(), amps_copy, n_harmonics, harms_copy, f0, phaseBuffer_in, (double)*additiveShiftParameter, (double)*additiveStretchParameter, addBuffer, phaseBuffer_out);
    }
    else {
        for (int i = 0; i < 4096; i++)
        {
            addBuffer[i] = 0;
        }
    }


    if (*noiseOnParameter)
    {
        subtractive(numSamples, mags_copy, (double)*noiseColorParameter, initial_bias, subBuffer);
    }
    else {
        for (int i = 0; i < 4096; i++)
        {
            subBuffer[i] = 0;
        }
    }
    for (int i = 0; i < 50; ++i) {
        phaseBuffer_in[i] = phaseBuffer_out[i];
    }

    auto outL = buffer.getWritePointer(0);
    auto outR = buffer.getWritePointer(1);

    for (int i = 0; i < buffer.getNumSamples(); i++) {
        float additiveGain = pow(10.0f,(*additiveGainParameter/20));
        float noiseGain = pow(10.0f,(*noiseGainParameter/20));
        float out = addBuffer[i] * additiveGain + subBuffer[i] * noiseGain;
        pushNextSampleIntoFifo(out);
        outL[i] = out;
        outR[i] = out;
    }
}

void DdspsynthAudioProcessor::setModelOutput(TensorflowHandler::ModelResults tfResults)
{
    // generated additive synth code overwrites passed harmonics & magnitudes
    // so create copy before passing
    for (int i = 0; i < 50; i++) {
        harmonics[i] = tfResults.harmonicDistribution[i];
    }
    for (int i = 0; i < 65; i++) {
        magnitudes[i] = tfResults.noiseMagnitudes[i];
    }
    //int amp_step = floor(numSamples / 100.0f);
    for (int i = 0; i < numSamples; i++) {
        //amplitudes[i] = tfResults.amplitudes[(int)floor(i / amp_step)];
        amplitudes[i] = tfResults.amplitudes[0];
    }

}

void DdspsynthAudioProcessor::handleAsyncUpdate()
{
    setModelOutput(tfHandler.getOutputs());
    DBG("Got output");
}


//==============================================================================
bool DdspsynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DdspsynthAudioProcessor::createEditor()
{
    return new DdspsynthAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void DdspsynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DdspsynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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

void DdspsynthAudioProcessor::pushNextSampleIntoFifo (float sample) noexcept
{
    // if the fifo contains enough data, set a flag to say
    // that the next line should now be rendered..
    if (fifoIndex == fftSize)
    {
        if (! nextFFTBlockReady)
        {
            juce::zeromem (fftData, sizeof (fftData));
            memcpy (fftData, fifo, sizeof (fifo));
            nextFFTBlockReady = true;
        }

        fifoIndex = 0;
    }

    fifo[fifoIndex++] = sample;
}
