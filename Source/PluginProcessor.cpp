/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "DDSPVoice.h"
#include "PluginEditor.h"
#include "HarmonicEditor.h"

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
    voice = new DDSPVoice();
	synth.addVoice(voice);

	synth.addSound(new DDSPSound());
}

DdspsynthAudioProcessor::~DdspsynthAudioProcessor()
{
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

void DdspsynthAudioProcessor::onSubAmpChange(double subAmp)
{
    voice->setSubAmp(subAmp);
}

