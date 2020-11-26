/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "DDSPVoice.h"
#include "PluginEditor.h"
#include "HarmonicEditor.h"
#include "codegen/additive.h"
#include "codegen/subtractive.h"
#include "codegen/getPitch2.h"
#include "codegen/getMagnitudes.h"

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
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    for (int i = 0; i < 50; i++) {
        harmonics[i] = 0.5;
    }
    fs = sampleRate;
    synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int i = 0; i < 50; ++i) {
        phaseBuffer_in[i] = 0;
    }
}

void DdspsynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
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
    if (inputIsLine) {
        auto* inputL = buffer.getReadPointer(0);
        int n_samples = buffer.getNumSamples();
        
        double rmsLevel = (double)buffer.getRMSLevel(0, 0, n_samples) * 10.0;
        for (int i = 0; i < n_samples; i++) {
            input[i] = (double)inputL[i];
            amplitudes[i] = rmsLevel;
        }
         
        getMagnitudes(n_samples, input, magnitudes);
        for (int i = 0; i < 65; i++) {
            magnitudes[i] = magnitudes[i] * rmsLevel;
        }

        double harms_copy[50];
        for (int i = 0; i < 50; i++) {
            harms_copy[i] = harmonics[i];
        }

        double f0 = getPitch2(n_samples, input, fs);

        double f0_array[4096];
        for (int i = 0; i < n_samples; i++) {
            f0_array[i] = f0;
        }

        int audio_size[1];
        additive(n_samples, fs, amplitudes, harmonics, f0_array, phaseBuffer_in, shift, stretch, addBuffer, audio_size, phaseBuffer_out);
        for (int i = 0; i < 50; ++i) {
            phaseBuffer_in[i] = phaseBuffer_out[i];
        }
        subtractive(n_samples, magnitudes, color, subBuffer);
        
        float* outL = buffer.getWritePointer(0);
        float* outR = buffer.getWritePointer(1);

        for (int i = 0; i < n_samples; i++) {
            outL[i] = (float)addBuffer[i] + (float)subBuffer[i];
            outR[i] = (float)addBuffer[i] + (float)subBuffer[i]; 
        }
    }
    else { // input is Midi
        synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    }
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

void DdspsynthAudioProcessor::onShiftValueChange(double shiftValue)
{
    voice->setShift(shiftValue);
}

void DdspsynthAudioProcessor::onStretchValueChange(double stretchValue)
{
    voice->setStretch(stretchValue);
}
