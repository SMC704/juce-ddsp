/*
  ==============================================================================

    DDSPAudioSource.cpp
    Created: 11 Nov 2020 4:26:10pm
    Author:  david

  ==============================================================================
*/

#include "DDSPVoice.h"
#include "codegen/additive.h"
#include "codegen/subtractive.h"

DDSPVoice::DDSPVoice()
{
	for (int i = 65; i
                       \
                        \
                         \
                          --> 0;) {
		magnitudes[i] = -10;
	}

	for (int i = 0; i < 4096; i++) {
		amplitudes[i] = 1;
		f0[i] = 440;
	}
	for (int i = 0; i < 50; i++) {
		harmonics[i] = 0.5;
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
	// generated additive synth code overwrites passed harmonics
	// so create copy before passing
	double harms_copy[50];
	for (int i = 0; i < 50; i++) {
		harms_copy[i] = harmonics[i];
	}

	int audio_size[1];

	additive(numSamples, getSampleRate(), amplitudes, harms_copy, f0, phaseBuffer_in, addBuffer, audio_size, phaseBuffer_out);
	jassert(numSamples == audio_size[0]);

	if (subtractiveOnOff)
	{
		subtractive(numSamples, magnitudes, color, subBuffer);
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



	for (int i = 0; i < numSamples && i < 4096; i++) {
		float val = (float)(addBuffer[i]*0.1 + subBuffer[i]);
		*(outputBuffer.getWritePointer(0, i)) = val;
		*(outputBuffer.getWritePointer(1, i)) = val;
	}
}
void DDSPVoice::setHarmonics(double harms[50])
{
	for (int i = 0; i < 50; i++) {
		harmonics[i] = harms[i];
	}
}

void DDSPVoice::setNoiseColor(double _color) 
{
	color = _color;
}

void DDSPVoice::setOnOffSubtractive(bool _button)
{
	subtractiveOnOff = _button;
}