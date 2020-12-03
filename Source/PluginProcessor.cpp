/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "DDSPVoice.h"
#include "PluginEditor.h"
#include "HarmonicEditor.h"
#include "tensorflow_c/include/tensorflow/c/c_api.h"

void NoOpDeallocator(void* data, size_t a, void* b) {}
//==============================================================================
DdspsynthAudioProcessor::DdspsynthAudioProcessor() : forwardFFT(fftOrder)
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
{

    tfGraph = TF_NewGraph();
    tfStatus = TF_NewStatus();
    tfSessionOpts = TF_NewSessionOptions();
    tfSession = TF_LoadSessionFromSavedModel(tfSessionOpts, tfRunOpts, saved_model_dir, &tags, ntags, tfGraph, NULL, tfStatus);
    if (TF_GetCode(tfStatus) == TF_OK)
    {
        DBG("TF_LoadSessionFromSavedModel OK\n");
    }
    else
    {
        DBG("%s", TF_Message(tfStatus));
    }

    tfInput = (TF_Output*)malloc(sizeof(TF_Output) * numInputs);
    f0Input = { TF_GraphOperationByName(tfGraph, "serving_default_input_1"), 0 };
    ldInput = { TF_GraphOperationByName(tfGraph, "serving_default_input_2"), 0 };

    tfInput[0] = f0Input;
    tfInput[1] = ldInput;

    tfOutput = (TF_Output*)malloc(sizeof(TF_Output) * numOutputs);
    ampsOutput = { TF_GraphOperationByName(tfGraph, "StatefulPartitionedCall"), 0 };
    harmsOutput = { TF_GraphOperationByName(tfGraph, "StatefulPartitionedCall"), 1 };
    magsOutput = { TF_GraphOperationByName(tfGraph, "StatefulPartitionedCall"), 2 };

    tfOutput[0] = ampsOutput;
    tfOutput[1] = harmsOutput;
    tfOutput[2] = magsOutput;

    tfInputValues = (TF_Tensor**)malloc(sizeof(TF_Tensor*) * numInputs);
    tfOutputValues = (TF_Tensor**)malloc(sizeof(TF_Tensor*) * numOutputs);

    voice = new DDSPVoice();
	synth.addVoice(voice);

	synth.addSound(new DDSPSound());
}

DdspsynthAudioProcessor::~DdspsynthAudioProcessor()
{
    TF_DeleteGraph(tfGraph);
    TF_DeleteSession(tfSession, tfStatus);
    TF_DeleteSessionOptions(tfSessionOpts);
    TF_DeleteStatus(tfStatus);
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
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	synth.setCurrentPlaybackSampleRate(sampleRate);
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
    f0InputTensor = TF_NewTensor(TF_FLOAT, inputDims, numInputDims, f0Data, ndata, &NoOpDeallocator, 0);
    ldInputTensor = TF_NewTensor(TF_FLOAT, inputDims, numInputDims, ldData, ndata, &NoOpDeallocator, 0);

    tfInputValues[0] = f0InputTensor;
    tfInputValues[1] = ldInputTensor;
    TF_SessionRun(tfSession, NULL, tfInput, tfInputValues, numInputs, tfOutput, tfOutputValues, numOutputs, NULL, 0, NULL, tfStatus);
    if (TF_GetCode(tfStatus) == TF_OK)
        DBG("Session is OK\n");
    else
        DBG("%s", TF_Message(Status));
	synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	for (int i = 0; i < buffer.getNumSamples(); i++) {
		this->pushNextSampleIntoFifo(*(buffer.getReadPointer(0, i)));
	}
}

//==============================================================================
bool DdspsynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DdspsynthAudioProcessor::createEditor()
{
    return new DdspsynthAudioProcessorEditor (*this);
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


void DdspsynthAudioProcessor::onValueChange(double harmonics[50])
{
	voice->setHarmonics(harmonics);
}

void DdspsynthAudioProcessor::onNoiseColorChange(double color)
{
    voice->setNoiseColor(color);
}

void DdspsynthAudioProcessor::onOnOffSubChange(bool onOff)
{
    voice->setOnOffSubtractive(onOff);
}

void DdspsynthAudioProcessor::onSubAmpChange(double subAmp)
{
    voice->setSubAmp(subAmp);
}

void DdspsynthAudioProcessor::onAddAmpChange(double addAmp)
{
    voice->setAddAmp(addAmp);
}

void DdspsynthAudioProcessor::onOutAmpChange(double outAmp)
{
    voice->setOutAmp(outAmp);
}

void DdspsynthAudioProcessor::onShiftValueChange(double shiftValue)
{
    voice->setShift(shiftValue);
}

void DdspsynthAudioProcessor::onStretchValueChange(double stretchValue)
{
    voice->setStretch(stretchValue);
}

void DdspsynthAudioProcessor::onOnOffAddChange(bool button)
{
    voice->setOnOffAdditive(button);
}
