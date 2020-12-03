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

void NoOpDeallocator(void* data, size_t a, void* b) {}
DDSPVoice::DDSPVoice()
{
	for (int i = 65; i
                       \
                        \
                         \
                          --> 0;) {
		magnitudes[i] = 1;
	}

	for (int i = 0; i < 4096; i++) {
		amplitudes[i] = 2;
		f0[i] = 440;
	}
	for (int i = 0; i < 50; i++) {
		harmonics[i] = 0.5;
	}

	for (int i = 0; i < 4096; i++)
	{
		ldData[i] = 0.5;
	}

	adsr.setSampleRate(getSampleRate());
	adsr_params.attack = 0.1;
	adsr_params.decay = 0.1;
	adsr_params.sustain = 1;
	adsr_params.release = 0.5;
	adsr.setParameters(adsr_params);
    
    shift = 0.0;
    stretch = 0.0;

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

	tfInputValues = (TF_Tensor**)malloc(sizeof(TF_Tensor*)*numInputs);
	tfOutputValues = (TF_Tensor**)malloc(sizeof(TF_Tensor*)*numOutputs);
}

DDSPVoice::~DDSPVoice()
{
	TF_DeleteGraph(tfGraph);
	TF_DeleteSession(tfSession, tfStatus);
	TF_DeleteSessionOptions(tfSessionOpts);
	TF_DeleteStatus(tfStatus);
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
	
	if (playing_model)
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

		
	}

	else {
		// generated additive synth code overwrites passed harmonics & magnitudes
		// so create copy before passing
		double harms_copy[50];
		double mags_copy[65];
		for (int i = 0; i < 50; i++) {
			harms_copy[i] = harmonics[i];
		}
		for (int i = 0; i < 65; i++) {
			mags_copy[i] = magnitudes[i];
		}

		int audio_size[1];

		if (additiveOnOff)
		{
			additive(numSamples, getSampleRate(), amplitudes, harms_copy, f0, phaseBuffer_in, shift, stretch, addBuffer, audio_size, phaseBuffer_out);
			jassert(numSamples == audio_size[0]);
		}
		else {
			for (int i = 0; i < 4096; i++)
			{
				addBuffer[i] = 0;
			}
		}

		if (subtractiveOnOff)
		{
			subtractive(numSamples, mags_copy, color, irBuffer_in, recalculateIR, subBuffer, irBuffer_out);
			if (recalculateIR);
			{
				recalculateIR = false;
				for (int i = 0; i < 129; i++)
					irBuffer_in[i] = irBuffer_out[i];
			}
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

		for (int i = startSample; i < startSample + numSamples && i < 4096; i++) {
			if (!adsr.isActive()) {
				// We are at the end of the release part
				clearCurrentNote();
				break;
			}
			float val = adsr.getNextSample() * (float)(addBuffer[i - startSample] * std::pow(10, addAmp / 20)) + (subBuffer[i - startSample] * std::pow(10, subAmp / 20));

			val = val * std::pow(10, outAmp / 20);

			*(outputBuffer.getWritePointer(0, i)) = val;
			*(outputBuffer.getWritePointer(1, i)) = val;
		}
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
void DDSPVoice::setOnOffSubtractive(bool _button)
{
	subtractiveOnOff = _button;
}

void DDSPVoice::setOnOffAdditive(bool _button)
{
	additiveOnOff = _button;
}
