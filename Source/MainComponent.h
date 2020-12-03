/*
  ==============================================================================

    MainComponent.h
    Created: 9 Nov 2020 11:22:48pm
    Author:  Robin Otterbein

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "InputComponent.h"
#include "ModelComponent.h"
#include "AdditiveComponent.h"
#include "SubtractiveComponent.h"
#include "ModulationComponent.h"
#include "ReverbComponent.h"
#include "SpectogramComponent.h"
#include "OutputComponent.h"

//==============================================================================
/*
*/
class MainComponent  : public juce::Component
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    //===============================================================================
    void drawNextLineOfSpectrogram(int fftSize, float* fftData, juce::dsp::FFT& forwardFFT, int fftOrder);

private:
    
    InputComponent inputComponent;
    ModelComponent modelComponent;
    AdditiveComponent additiveComponent;
    SubtractiveComponent subtractiveComponent;
    ModulationComponent modulationComponent;
    ReverbComponent reverbComponent;
    SpectogramComponent spectogramComponent;
    OutputComponent outputComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
