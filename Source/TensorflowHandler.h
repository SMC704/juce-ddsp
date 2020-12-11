/*
  ==============================================================================

    TensorflowHandler.h
    Created: 3 Dec 2020 4:39:32pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "tensorflow_c/include/tensorflow/c/c_api.h"

class TensorflowHandler : public juce::Thread
{
public:
	TensorflowHandler();
	~TensorflowHandler();

	// TODO: this should probably be read from a gin file
	// or possibly the model file?
	static const int numHarmonics = 60;
	static const int numMagnitudes = 65;
	static const int timeSteps = 1;

	struct ModelResults
	{
		float amplitudes[timeSteps];
		float harmonicDistribution[timeSteps * numHarmonics];
		float noiseMagnitudes[timeSteps * numMagnitudes];
	};

	typedef struct ModelResults ModelResults;

	void loadModel(const char* path);
	void unloadModel();
	void setInputs(float f0, float amps);
	void setAsyncUpdater(juce::AsyncUpdater* _asyncUpdater) { processUpdater = _asyncUpdater; };
	ModelResults getOutputs() { return results; };

	void run() override;

private:
	//DdspsynthAudioProcessor* audioProcessor;

	juce::CriticalSection lock;

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
	TF_Output* tfOutput = NULL;
	TF_Output ampsOutput;
	TF_Output harmsOutput;
	TF_Output magsOutput;

	TF_Tensor** tfInputValues = NULL;
	TF_Tensor** tfOutputValues = NULL;

	int numInputDims = 3;
	int64_t inputDims[3] = { 1,timeSteps,1 };

	int ntags = 1;

	const char* tags = "serve";

	int ndata = TF_DataTypeSize(TF_FLOAT) * timeSteps;
	TF_Tensor* f0InputTensor;
	TF_Tensor* ldInputTensor;
	
	ModelResults results;

	juce::AsyncUpdater* processUpdater;
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TensorflowHandler)
};