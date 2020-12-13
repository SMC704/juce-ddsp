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

	juce::DynamicLibrary tfLibrary;

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

	int ndata = 4 * timeSteps;
	TF_Tensor* f0InputTensor;
	TF_Tensor* ldInputTensor;
	
	ModelResults results;

	juce::AsyncUpdater* processUpdater;

	typedef TF_Graph* (*fptypeNewGraph) ();
	fptypeNewGraph fpNewGraph;

	typedef void (*fptypeDeleteGraph) (TF_Graph*);
	fptypeDeleteGraph fpDeleteGraph;

	typedef TF_Status* (*fptypeNewStatus) ();
	fptypeNewStatus fpNewStatus;

	typedef void (*fptypeDeleteStatus) (TF_Status*);
	fptypeDeleteStatus fpDeleteStatus;

	typedef TF_SessionOptions* (*fptypeNewSessionOpts) ();
	fptypeNewSessionOpts fpNewSessionOpts;

	typedef void (*fptypeDeleteSessionOptions) (TF_SessionOptions*);
	fptypeDeleteSessionOptions fpDeleteSessionOptions;

	typedef TF_Session* (*fptypeLoadSession) (
		const TF_SessionOptions*, const TF_Buffer*,
		const char*, const char* const*, int,
		TF_Graph*, TF_Buffer*, TF_Status*
	);
	fptypeLoadSession fpLoadSession;

	typedef void (*fptypeDeleteSession) (TF_Session*, TF_Status*);
	fptypeDeleteSession fpDeleteSession;

	typedef TF_Operation* (*fptypeGraphOperation) (TF_Graph*, const char*);
	fptypeGraphOperation fpGraphOperation;

	typedef TF_Tensor* (*fptypeNewTensor) (
		TF_DataType, const int64_t*, int, void*, size_t,
		void(*deallocator)(void* data, size_t len, void* arg), void*
	);
	fptypeNewTensor fpNewTensor;

	typedef void (*fptypeDeleteTensor) (TF_Tensor*);
	fptypeDeleteTensor fpDeleteTensor;

	typedef void* (*fptypeTensorData) (const TF_Tensor*);
	fptypeTensorData fpTensorData;

	typedef void(*fptypeSessionRun) (
		TF_Session*, const TF_Buffer* run_options,
		const TF_Output*, TF_Tensor* const*, int,
		const TF_Output*, TF_Tensor**, int,
		const TF_Operation* const*, int,
		TF_Buffer*, TF_Status*
	);
	fptypeSessionRun fpSessionRun;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TensorflowHandler)
};