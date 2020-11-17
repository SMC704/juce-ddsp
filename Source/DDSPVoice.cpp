/*
  ==============================================================================

    DDSPAudioSource.cpp
    Created: 11 Nov 2020 4:26:10pm
    Author:  david

  ==============================================================================
*/

#include "DDSPVoice.h"

DDSPVoice::DDSPVoice()
{
	for (int i = 0; i < 1024; i++) {
		amplitudes[i] = 1;
		f0[i] = 440;
		for (int j = 0; j < 50; j++) {
			harmonics[i * 50 + j] = 0.5;
		}
	}
}

bool DDSPVoice::canPlaySound(juce::SynthesiserSound * sound)
{
	return dynamic_cast<DDSPSound*> (sound) != nullptr;
}

void DDSPVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound * sound, int)
{
	double freq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	for (int i = 0; i < 1024; i++) {
		f0[i] = freq;
	}
}

void DDSPVoice::stopNote(float, bool allowTailOff)
{
	clearCurrentNote();
}

void DDSPVoice::renderNextBlock(juce::AudioSampleBuffer & outputBuffer, int startSample, int numSamples)
{
	double harms[1024 * 50];
	for (int i = 0; i < 1024 * 50; i++) {
		harms[i] = harmonics[i];
	}
	additive(getSampleRate(), amplitudes, harms, f0, phaseBuffer_in, audioBuffer, phaseBuffer_out);
	for (int i = 0; i < 50; ++i) {
		phaseBuffer_in[i] = phaseBuffer_out[i];
	}

	for (int i = 0; i < 1024 && i < outputBuffer.getNumSamples(); i++) {
		*(outputBuffer.getWritePointer(0, i)) = (float)audioBuffer[i];
		*(outputBuffer.getWritePointer(1, i)) = (float)audioBuffer[i];
	}
}
void DDSPVoice::setHarmonics(double harms[50])
{
	for (int i = 0; i < 1024; i++) {
		for (int j = 0; j < 50; j++) {
			harmonics[i * 50 + j] = harms[i];
		}
	}
}
;