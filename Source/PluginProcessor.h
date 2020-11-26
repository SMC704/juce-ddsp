/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DDSPVoice.h"
#include "HarmonicEditor.h"
#include "SubtractiveComponent.h"
#include "AdditiveComponent.h"
//==============================================================================
/**
*/
class DdspsynthAudioProcessor : public juce::AudioProcessor, public HarmonicEditor::Listener
{
public:
    //==============================================================================
    DdspsynthAudioProcessor();
    ~DdspsynthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    void pushNextSampleIntoFifo (float sample) noexcept;
    
    int getFftSize() { return fftSize; };
    int getFftOrder() { return fftOrder; };
    float* getFftData() { return &fftData[0]; };
    bool getNextFFTBlockReady() { return nextFFTBlockReady; };
    juce::dsp::FFT *getForwardFFT() { return &forwardFFT; };

    void setNextFFTBlockReady(bool nextFFTBlockReady_) { nextFFTBlockReady = nextFFTBlockReady_; };
    
    enum
    {
        fftOrder = 10,
        fftSize  = 1 << fftOrder
    };

	void onValueChange(double harmonics[50]);
    
    void onShiftValueChange(double shiftValue);

    void onStretchValueChange(double stretchValue);

    void onNoiseColorChange(double color);
    void onOnOffSubChange(bool onOff);
    void onSubAmpChange(double subAmp);
    void onAddAmpChange(double addAmp);
    void onOutAmpChange(double outAmp);

    void onOnOffAddChange(bool button);

private:
    juce::dsp::FFT forwardFFT;
    
    float fifo [fftSize];
    float fftData [2 * fftSize];
    int fifoIndex = 0;
    bool nextFFTBlockReady = false;
    
    //==============================================================================
	DDSPVoice* voice;
	juce::MidiKeyboardState keyboardState;
	juce::Synthesiser synth;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DdspsynthAudioProcessor)
};
