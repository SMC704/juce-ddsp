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
#include <math.h>
#include <stdlib.h>


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
		amplitudes[i] = 2;
		f0[i] = 440;
	}
	for (int i = 0; i < 50; i++) {
		harmonics[i] = 0.5;
	}

	adsr.setSampleRate(getSampleRate());
	adsr_params.attack = 0.1;
	adsr_params.decay = 0.1;
	adsr_params.sustain = 1;
	adsr_params.release = 0.5;
	adsr.setParameters(adsr_params);
}

bool DDSPVoice::canPlaySound(juce::SynthesiserSound * sound)
{
	return dynamic_cast<DDSPSound*> (sound) != nullptr;
}

void DDSPVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound * sound, int)
{
	adsr.reset();
	adsr.noteOn();

	double freq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	for (int i = 0; i < 4096; i++) {
		f0[i] = freq;
	}
}

void DDSPVoice::stopNote(float, bool allowTailOff)
{
	if (allowTailOff)
		adsr.noteOff();
	else
		adsr.reset();
}

void DDSPVoice::renderNextBlock(juce::AudioSampleBuffer & outputBuffer, int startSample, int numSamples)
{
	if (!adsr.isActive()) return;
	
	// generated additive synth code overwrites passed harmonics
	// so create copy before passing
	double harms_copy[50];
	for (int i = 0; i < 50; i++) {
		harms_copy[i] = harmonics[i];
	}

	int audio_size[1];

	additive(numSamples, getSampleRate(), amplitudes, harms_copy, f0, phaseBuffer_in, shift, stretch, addBuffer, audio_size, phaseBuffer_out);
	jassert(numSamples == audio_size[0]);
	subtractive(numSamples, magnitudes, color, subBuffer);
	for (int i = 0; i < 50; ++i) {
		phaseBuffer_in[i] = phaseBuffer_out[i];
	}

	for (int i = 0; i < numSamples && i < 4096; i++) {
		if (!adsr.isActive()) {
			// We are at the end of the release part

			clearCurrentNote();

			// fill the buffer with zeros and leave loop
			for (int j = i; j < numSamples && j < 4096; j++) {
				*(outputBuffer.getWritePointer(0, i)) = 0;
				*(outputBuffer.getWritePointer(1, i)) = 0;
			}
			break;
		}
		float val = adsr.getNextSample() * (float)(addBuffer[i]*std::pow(10, addAmp/20)) + (subBuffer[i]*std::pow(10, subAmp/20));
        
        val = val * std::pow(10, outAmp/20);

		*(outputBuffer.getWritePointer(0, i)) = val;
		*(outputBuffer.getWritePointer(1, i)) = val;
	}
}
void DDSPVoice::setHarmonics(double harms[50])
{
	for (int i = 0; i < 50; i++) {
        
        float value = 1 - harms[i];
        
        if (value > 1.0f)
            value = 1.0f;
        if (value < 0.0f)
            value = 0.0f;
        
		harmonics[i] = value;
	}
}

void DDSPVoice::setNoiseColor(double _color) 
{
	color = _color;
}

void DDSPVoice::setSubAmp(double _subAmp)
{
    subAmp = _subAmp;
}

void DDSPVoice::setAddAmp(double _addAmp)
{
    addAmp = _addAmp;
}

void DDSPVoice::setOutAmp(double _outAmp)
{
    outAmp = _outAmp;
}
