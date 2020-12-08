/*
  ==============================================================================

    TensorflowHandler.cpp
    Created: 3 Dec 2020 4:39:32pm
    Author:  david

  ==============================================================================
*/

#include "TensorflowHandler.h"
#include <cstdlib>

void NoOpDeallocator(void* data, size_t a, void* b) {}

TensorflowHandler::TensorflowHandler()
{

}

TensorflowHandler::~TensorflowHandler()
{
	unloadModel();
}

void TensorflowHandler::unloadModel()
{
	if (tfGraph != NULL)
	{
		TF_DeleteTensor(f0InputTensor);
		TF_DeleteTensor(ldInputTensor);
		free(tfInputValues);
		free(tfOutputValues);
		free(tfOutput);
		free(tfInput);
		TF_DeleteSession(tfSession, tfStatus);
		TF_DeleteSessionOptions(tfSessionOpts);
		TF_DeleteStatus(tfStatus);
		TF_DeleteGraph(tfGraph);

		tfGraph = NULL;
		tfStatus = NULL;
		tfSessionOpts = NULL;
		tfSession = NULL;
		tfInput = NULL;
		tfOutput = NULL;
		tfInputValues = NULL;
		tfOutputValues = NULL;
		f0InputTensor = NULL;
		ldInputTensor = NULL;
	}
}

void TensorflowHandler::loadModel(const char* path)
{
	tfGraph = TF_NewGraph();
	tfStatus = TF_NewStatus();
	tfSessionOpts = TF_NewSessionOptions();
	tfSession = TF_LoadSessionFromSavedModel(tfSessionOpts, tfRunOpts, path, &tags, ntags, tfGraph, NULL, tfStatus);
	
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

	tfInputValues = (TF_Tensor**)malloc(sizeof(TF_Tensor*) * numInputs);
	tfOutputValues = (TF_Tensor**)malloc(sizeof(TF_Tensor*) * numOutputs);

	float dummy[timeSteps];

	f0InputTensor = TF_NewTensor(TF_FLOAT, inputDims, numInputDims, dummy, ndata, &NoOpDeallocator, 0);
	ldInputTensor = TF_NewTensor(TF_FLOAT, inputDims, numInputDims, dummy, ndata, &NoOpDeallocator, 0);

	tfInputValues[0] = f0InputTensor;
	tfInputValues[1] = ldInputTensor;
}

TensorflowHandler::ModelResults TensorflowHandler::runModel(float f0[TensorflowHandler::timeSteps], float amps[TensorflowHandler::timeSteps])
{
	TensorflowHandler::ModelResults results;

	float* f0InputData = (float*)TF_TensorData(f0InputTensor);
	float* ldInputData = (float*)TF_TensorData(ldInputTensor);

	for (int t = 0; t < timeSteps; t++)
	{
		f0InputData[t] = f0[t];
		ldInputData[t] = amps[t];
	}

	TF_SessionRun(tfSession, NULL, tfInput, tfInputValues, numInputs, tfOutput, tfOutputValues, numOutputs, NULL, 0, NULL, tfStatus);

	float* ampsOutputData = (float*)TF_TensorData(tfOutputValues[0]);
	float* harmsOutputData = (float*)TF_TensorData(tfOutputValues[1]);
	float* magsOutputData = (float*)TF_TensorData(tfOutputValues[2]);

	for (int t = 0; t < timeSteps; t++)
		results.amplitudes[t] = ampsOutputData[t];

	for (int h = 0; h < timeSteps * numHarmonics; h++)
		results.harmonicDistribution[h] = harmsOutputData[h];

	for (int m = 0; m < timeSteps * numMagnitudes; m++)
		results.noiseMagnitudes[m] = magsOutputData[m];
	
	return results;
}