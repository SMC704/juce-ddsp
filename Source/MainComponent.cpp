/*
  ==============================================================================

    MainComponent.cpp
    Created: 9 Nov 2020 11:22:48pm
    Author:  Robin Otterbein

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent(juce::AudioProcessorValueTreeState& svts, juce::AudioProcessorValueTreeState& mvts)
    : inputComponent(svts), modelComponent(mvts), additiveComponent(svts), 
    subtractiveComponent(svts), modulationComponent(svts), reverbComponent(svts),
    outputComponent(svts)
{
    addChildAndSetID(&inputComponent, "input");
    addChildAndSetID(&modelComponent, "model");
    addChildAndSetID(&additiveComponent, "additive");
    addChildAndSetID(&subtractiveComponent, "subtractive");
    addChildAndSetID(&modulationComponent, "modulation");
    addChildAndSetID(&reverbComponent, "reverb");
    addChildAndSetID(&spectogramComponent, "spectogram");
    addChildAndSetID(&outputComponent, "output");
    inputComponent.setBounds(0, 0, 200, 200);
    modelComponent.setBounds(0, 0, 200, 200);
    additiveComponent.setBounds(0, 0, 200, 200);
    subtractiveComponent.setBounds(0, 0, 200, 200);
    modulationComponent.setBounds(0, 0, 200, 200);
    reverbComponent.setBounds(0, 0, 200, 200);
    spectogramComponent.setBounds(0, 0, 200, 200);
    outputComponent.setBounds(0, 0, 200, 200);
    
    // Grey out not implemented components
    modulationComponent.setEnabled(false);
    reverbComponent.setEnabled(false);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (juce::Graphics& g)
{
    
}

void MainComponent::resized()
{
    juce::Grid grid;
     
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows    = {
        Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1)),
        Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1))
    };
    grid.templateColumns = {
        Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1)),
        Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1)),
        Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1))
    };
    
    grid.rowGap = juce::Grid::Px(10.0f);
    grid.columnGap = juce::Grid::Px(10.0f);


    grid.items = {

        juce::GridItem (inputComponent).withArea(2, 1, 2, 4),
        juce::GridItem (modelComponent).withArea(3, 1, 9, 4),
        juce::GridItem (additiveComponent).withArea(2, 4, 6, 10),
        juce::GridItem (subtractiveComponent).withArea(6, 4, 9, 6),
        juce::GridItem (modulationComponent).withArea(6, 6, 9, 8),
        juce::GridItem (reverbComponent).withArea(6, 8, 9, 10),
        juce::GridItem (outputComponent).withArea(2, 10, 2, 13),
        juce::GridItem (spectogramComponent).withArea(3, 10, 9, 13),
        
     };


    
    grid.performLayout (getLocalBounds());
}

//==============================================================================
// Spectrogram methods
void MainComponent::drawNextLineOfSpectrogram(int fftSize, float* fftData, juce::dsp::FFT& forwardFFT, int fftOrder)
{
    spectogramComponent.drawNextLineOfSpectrogram(fftSize, fftData, forwardFFT, fftOrder);
}
