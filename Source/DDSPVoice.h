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
#include "tensorflow_c/include/tensorflow/c/c_api.h"

class DDSPVoice : public juce::SynthesiserVoice
{

public:

	DDSPVoice();
	~DDSPVoice();

	void pitchWheelMoved(int) override {};
	void controllerMoved(int, int) override {};

	bool canPlaySound(juce::SynthesiserSound* sound) override;

	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int /*currentPitchWheelPosition*/) override;

	void stopNote(float /*velocity*/, bool allowTailOff) override;

	void renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;

	void setHarmonics(double harms[50]);

	void setNoiseColor(double color);
	void setSubAmp(double subAmp);
	void setAddAmp(double addAmp);
	void setOutAmp(double outAmp);
	
	void setShift(double _shift) { shift = _shift; };

	void setStretch(double _stretch) { stretch = _stretch; };

	void setOnOffSubtractive(bool button);

	void setOnOffAdditive(bool button);

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
	double addAmp = 0;
	double outAmp = 0;
	bool subtractiveOnOff = false;
	bool additiveOnOff = false;

	double irBuffer_in[129];
	double irBuffer_out[129];
	bool recalculateIR = true;

	bool tailoff = false;

	juce::ADSR adsr;
	juce::ADSR::Parameters adsr_params;
	juce::Random r;

	TF_Graph* tfGraph = NULL;
	TF_Status* tfStatus = NULL;
	TF_SessionOptions* tfSessionOpts = NULL;
	TF_Session* tfSession = NULL;
	TF_Buffer* tfRunOpts = NULL;

	int numInputs = 2;
	TF_Output* tfInput = NULL;
	TF_Output f0Input;
	TF_Output ldInput;

	int numOutputs = 3;
	TF_Output* tfOutput;
	TF_Output ampsOutput;
	TF_Output harmsOutput;
	TF_Output magsOutput;

	TF_Tensor** tfInputValues;
	TF_Tensor** tfOutputValues;

	static const int time_steps = 100;

	int numInputDims = 3;
	int64_t inputDims[3] = { 1,100,1 };
	float f0Data[100];
	float ldData[100];

	float modelSampleRate = 44100;
	float samplesPerTimestep = modelSampleRate / time_steps;

	int modelSampleCounter = 0;

	int ntags = 1;

	const char* saved_model_dir = "C:\\Users\\david\\Documents\\Sound and Music Computing\\DDSP\\juce-ddsp\\Source\\Python\\functional";
	const char* tags = "serve";

	int ndata = TF_DataTypeSize(TF_FLOAT) * time_steps;
	TF_Tensor* f0InputTensor;
	TF_Tensor* ldInputTensor;

	bool playing_model = true;
};
