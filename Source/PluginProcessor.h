/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <cstdio>
#include "HarmonicEditor.h"
#include "SubtractiveComponent.h"
#include "AdditiveComponent.h"
#include "TensorflowHandler.h"
#include "aubio.h"
//==============================================================================
/**
*/
class DdspsynthAudioProcessor : public juce::AudioProcessor, juce::AsyncUpdater, juce::AudioProcessorValueTreeState::Listener, public HarmonicEditor::Listener
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

    void parseModelConfigJSON(juce::String path);
    void setModelOutput(TensorflowHandler::ModelResults results);

	void onHarmonicsChange(double* harmonics, int nHarmonics);
 //   
 //   void onShiftValueChange(double shiftValue);

 //   void onStretchValueChange(double stretchValue);

 //   void onNoiseColorChange(double color);
 //   void onOnOffSubChange(bool onOff);
 //   void onSubAmpChange(double subAmp);
 //   void onAddAmpChange(double addAmp);
 //   void onOutAmpChange(double outAmp);

 //   void onOnOffAddChange(bool button);

	void parameterChanged(const juce::String &parameterID, float newValue = 0) override;

private:

    // Parameters
    juce::AudioProcessorValueTreeState parameters;

    std::atomic<float>* inputSelectParameter = nullptr;
    std::atomic<float>* modelOnParameter = nullptr;
    std::atomic<float>* modelChoiceParameter = nullptr;
    std::atomic<float>* additiveOnParameter = nullptr;
    std::atomic<float>* additiveShiftParameter = nullptr;
    std::atomic<float>* additiveStretchParameter = nullptr;
    std::atomic<float>* additiveGainParameter = nullptr;
    std::atomic<float>* noiseOnParameter = nullptr;
    std::atomic<float>* noiseColorParameter = nullptr;
    std::atomic<float>* noiseGainParameter = nullptr;
    std::atomic<float>* modulationOnParameter = nullptr;
    std::atomic<float>* modulationRateParameter = nullptr;
    std::atomic<float>* modulationDelayParameter = nullptr;
    std::atomic<float>* modulationAmountParameter = nullptr;
    std::atomic<float>* reverbOnParameter = nullptr;
    std::atomic<float>* reverbMixParameter = nullptr;
    std::atomic<float>* reverbSizeParameter = nullptr;
    std::atomic<float>* reverbGlowParameter = nullptr;
    std::atomic<float>* outputGainParameter = nullptr;

    // Internal parameters
    double phaseBuffer_in[60];
    double phaseBuffer_out[60];
    double amplitudes[4096];
    double ld;
    double f0_in;
    double f0_out;
    double f0[4096];
    double n_harmonics = 60;
    double harmonics[60];
	double userHarmonics[60];
    double addBuffer[4096];
    double initial_bias = -5.0f;
    double subBuffer[4096];
    double magnitudes[65];
    double numSamples;

    // Midi features
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams = { 1.0f, 0.1f, 1.0f, 1.0f };
    float midiVelocity;
    float adsrVelocity;
    float midiNoteHz;

    // FFT Window
    juce::dsp::FFT forwardFFT;
    
    float fifo [fftSize];
    float fftData [2 * fftSize];
    int fifoIndex = 0;
    bool nextFFTBlockReady = false;

    // Tensorflow 
	TensorflowHandler tfHandler;
    TensorflowHandler::ModelResults tfResults;
    // TF test
    float tf_f0;
    float tf_amps;

	struct PitchDeleter
	{
		void operator()(aubio_pitch_t *p) { del_aubio_pitch(p); }
	};

	std::unique_ptr<aubio_pitch_t, PitchDeleter> aubioPitch;

	const juce::String modelDir = "../../Models/";

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DdspsynthAudioProcessor)


        // Inherited via AsyncUpdater
        virtual void handleAsyncUpdate() override;

};
