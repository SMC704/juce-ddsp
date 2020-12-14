/*
  ==============================================================================

    TensorflowHandler.cpp
    Created: 3 Dec 2020 4:39:32pm
    Author:  david

  ==============================================================================
*/

#include "TensorflowHandler.h"
#include <cstdlib>
#include <juce_core/juce_core.h>

void NoOpDeallocator(void* data, size_t a, void* b) {}


TensorflowHandler::TensorflowHandler()
	: Thread("TFThread")
{
#if JUCE_WINDOWS
	DBG("Loading TF LIB...");
    
	juce::File cwd = juce::File::getSpecialLocation(juce::File::currentApplicationFile).getParentDirectory();
    const char* libFileName = "tensorflow.dll";

    bool loaded = tfLibrary.open(cwd.getFullPathName() + juce::File::getSeparatorString() + libFileName);
	if (loaded)
		DBG("success");
	else
		DBG("fail");

	fpNewGraph = (fptypeNewGraph)tfLibrary.getFunction("TF_NewGraph");
	fpDeleteGraph = (fptypeDeleteGraph)tfLibrary.getFunction("TF_DeleteGraph");

	fpNewStatus = (fptypeNewStatus)tfLibrary.getFunction("TF_NewStatus");
	fpDeleteStatus = (fptypeDeleteStatus)tfLibrary.getFunction("TF_DeleteStatus");

	fpNewSessionOpts = (fptypeNewSessionOpts)tfLibrary.getFunction("TF_NewSessionOptions");
	fpDeleteSessionOptions = (fptypeDeleteSessionOptions)tfLibrary.getFunction("TF_DeleteSessionOptions");

	fpLoadSession = (fptypeLoadSession)tfLibrary.getFunction("TF_LoadSessionFromSavedModel");
	fpDeleteSession = (fptypeDeleteSession)tfLibrary.getFunction("TF_DeleteSession");

	fpGraphOperation = (fptypeGraphOperation)tfLibrary.getFunction("TF_GraphOperationByName");

	fpNewTensor = (fptypeNewTensor)tfLibrary.getFunction("TF_NewTensor");
	fpDeleteTensor = (fptypeDeleteTensor)tfLibrary.getFunction("TF_DeleteTensor");

	fpTensorData = (fptypeTensorData)tfLibrary.getFunction("TF_TensorData");

	fpSessionRun = (fptypeSessionRun)tfLibrary.getFunction("TF_SessionRun");
    
#endif
}


TensorflowHandler::~TensorflowHandler()
{
	unloadModel();
	tfLibrary.close();
}

void TensorflowHandler::unloadModel()
{
	if (tfGraph != NULL)
	{
#if JUCE_WINDOWS
		fpDeleteTensor(f0InputTensor);
		fpDeleteTensor(ldInputTensor);
		free(tfInputValues);
		free(tfOutputValues);
		free(tfOutput);
		free(tfInput);
		fpDeleteSession(tfSession, tfStatus);
		fpDeleteSessionOptions(tfSessionOpts);
		fpDeleteStatus(tfStatus);
		fpDeleteGraph(tfGraph);

#elif JUCE_MAC
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
        
#endif
        
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
	// make sure no one tries to run the model while we're changing it
	const juce::ScopedLock loadLock(lock);
	
	unloadModel();

#if JUCE_WINDOWS
	tfGraph = fpNewGraph();
	tfStatus = fpNewStatus();
	tfSessionOpts = fpNewSessionOpts();
	tfSession = fpLoadSession(tfSessionOpts, tfRunOpts, path, &tags, ntags, tfGraph, NULL, tfStatus);
	
	tfInput = (TF_Output*)malloc(sizeof(TF_Output) * numInputs);
	f0Input = { fpGraphOperation(tfGraph, "serving_default_input_1"), 0 };
	ldInput = { fpGraphOperation(tfGraph, "serving_default_input_2"), 0 };
	

	tfOutput = (TF_Output*)malloc(sizeof(TF_Output) * numOutputs);
	ampsOutput = { fpGraphOperation(tfGraph, "StatefulPartitionedCall"), 0 };
	harmsOutput = { fpGraphOperation(tfGraph, "StatefulPartitionedCall"), 1 };
	magsOutput = { fpGraphOperation(tfGraph, "StatefulPartitionedCall"), 2 };
    
#elif JUCE_MAC
    tfGraph = TF_NewGraph();
    tfStatus = TF_NewStatus();
    tfSessionOpts = TF_NewSessionOptions();
    tfSession = TF_LoadSessionFromSavedModel(tfSessionOpts, tfRunOpts, path, &tags, ntags, tfGraph, NULL, tfStatus);
    
    tfInput = (TF_Output*)malloc(sizeof(TF_Output) * numInputs);
    f0Input = { TF_GraphOperationByName(tfGraph, "serving_default_input_1"), 0 };
    ldInput = { TF_GraphOperationByName(tfGraph, "serving_default_input_2"), 0 };
    

    tfOutput = (TF_Output*)malloc(sizeof(TF_Output) * numOutputs);
    ampsOutput = { TF_GraphOperationByName(tfGraph, "StatefulPartitionedCall"), 0 };
    harmsOutput = { TF_GraphOperationByName(tfGraph, "StatefulPartitionedCall"), 1 };
    magsOutput = { TF_GraphOperationByName(tfGraph, "StatefulPartitionedCall"), 2 };
    
#endif

    tfInput[0] = f0Input;
    tfInput[1] = ldInput;
    
	tfOutput[0] = ampsOutput;
	tfOutput[1] = harmsOutput;
	tfOutput[2] = magsOutput;

	tfInputValues = (TF_Tensor**)malloc(sizeof(TF_Tensor*) * numInputs);
	tfOutputValues = (TF_Tensor**)malloc(sizeof(TF_Tensor*) * numOutputs);

	float f0Data[timeSteps];
	float ldData[timeSteps];

#if JUCE_WINDOWS
	f0InputTensor = fpNewTensor(TF_FLOAT, inputDims, numInputDims, f0Data, ndata, &NoOpDeallocator, 0);
	ldInputTensor = fpNewTensor(TF_FLOAT, inputDims, numInputDims, ldData, ndata, &NoOpDeallocator, 0);
    
#elif JUCE_MAC
    f0InputTensor = TF_NewTensor(TF_FLOAT, inputDims, numInputDims, f0Data, ndata, &NoOpDeallocator, 0);
    ldInputTensor = TF_NewTensor(TF_FLOAT, inputDims, numInputDims, ldData, ndata, &NoOpDeallocator, 0);
    
#endif

	tfInputValues[0] = f0InputTensor;
	tfInputValues[1] = ldInputTensor;
}

void TensorflowHandler::setInputs(float f0, float amps)
{	
	// this might/should be changed into ScopedTryLock and returning false
	const juce::ScopedLock loadLock(lock);

#if JUCE_WINDOWS
	float* f0InputData = (float*)fpTensorData(tfInputValues[0]);
	float* ldInputData = (float*)fpTensorData(tfInputValues[1]);
    
#elif JUCE_MAC
    float* f0InputData = (float*)TF_TensorData(tfInputValues[0]);
    float* ldInputData = (float*)TF_TensorData(tfInputValues[1]);
    
#endif

	f0InputData[0] = f0;
	ldInputData[0] = amps;
}


void TensorflowHandler::run()
{
	// this might/should be changed into ScopedTryLock and returning false
	const juce::ScopedLock loadLock(lock);

	TensorflowHandler::ModelResults _results;

#if JUCE_WINDOWS
	fpSessionRun(tfSession, NULL, tfInput, tfInputValues, numInputs, tfOutput, tfOutputValues, numOutputs, NULL, 0, NULL, tfStatus);

	float* ampsOutputData = (float*)fpTensorData(tfOutputValues[0]);
	float* harmsOutputData = (float*)fpTensorData(tfOutputValues[1]);
	float* magsOutputData = (float*)fpTensorData(tfOutputValues[2]);
    
#elif JUCE_MAC
    TF_SessionRun(tfSession, NULL, tfInput, tfInputValues, numInputs, tfOutput, tfOutputValues, numOutputs, NULL, 0, NULL, tfStatus);

    float* ampsOutputData = (float*)TF_TensorData(tfOutputValues[0]);
    float* harmsOutputData = (float*)TF_TensorData(tfOutputValues[1]);
    float* magsOutputData = (float*)TF_TensorData(tfOutputValues[2]);
    
#endif
    
	for (int t = 0; t < timeSteps; t++)
		_results.amplitudes[t] = ampsOutputData[t];

	for (int h = 0; h < timeSteps * numHarmonics; h++)
		_results.harmonicDistribution[h] = harmsOutputData[h];

	for (int m = 0; m < timeSteps * numMagnitudes; m++)
		_results.noiseMagnitudes[m] = magsOutputData[m];
	
	results = _results;

	processUpdater->triggerAsyncUpdate();
}
