/*
  ==============================================================================

    TensorflowHandler.h
    Created: 3 Dec 2020 4:39:32pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include "tensorflow_c/include/tensorflow/c/c_api.h"

class TensorflowHandler
{
public:
	TensorflowHandler();
	~TensorflowHandler();

	// TODO: this should probably be read from a gin file
	// or possibly the model file?
	static const int numHarmonics = 60;
	static const int numMagnitudes = 65;
	static const int timeSteps = 100;

	struct ModelResults
	{
		float amplitudes[timeSteps];
		float harmonicDistribution[timeSteps * numHarmonics];
		float noiseMagnitudes[timeSteps * numMagnitudes];
	};

	typedef struct ModelResults ModelResults;

	void loadModel(const char* path);
	void unloadModel();
	ModelResults runModel(float f0[timeSteps], float amps[timeSteps]);

private:
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
};