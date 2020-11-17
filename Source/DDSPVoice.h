/*
  ==============================================================================

    DDSPAudioSource.h
    Created: 11 Nov 2020 4:26:10pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "codegen/additive.h"
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

private:
	double phaseBuffer_in[50];
	double phaseBuffer_out[50];
	double amplitudes[1024];
	double f0[1024];
	double harmonics[1024 * 50];
	double audioBuffer[1024];
};
