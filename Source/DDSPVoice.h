/*
  ==============================================================================

    DDSPAudioSource.h
    Created: 11 Nov 2020 4:26:10pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DDSPSound.h"
#include "HarmonicEditor.h"

class DDSPVoice : public juce::SynthesiserVoice
{

public:

	DDSPVoice();
	~DDSPVoice() {};

	void pitchWheelMoved(int) override {};
	void controllerMoved(int, int) override {};

	bool canPlaySound(juce::SynthesiserSound* sound) override;

	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int /*currentPitchWheelPosition*/) override;

	void stopNote(float /*velocity*/, bool allowTailOff) override;

	void renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;

	void setHarmonics(double harms[50]);
	void setNoiseColor(double color);
    void setSubAmp(double subAmp);

private:
	double phaseBuffer_in[50];
	double phaseBuffer_out[50];
	double amplitudes[4096];
	double f0[4096];
	double harmonics[50];
	double addBuffer[4096];
	double subBuffer[4096];
	double magnitudes[65];
	double color = -1;
	double shift = 0;
	double stretch = 0;
    double subAmp = 0;

	bool tailoff = false;

	juce::ADSR adsr;
	juce::ADSR::Parameters adsr_params;
	juce::Random r;
};
