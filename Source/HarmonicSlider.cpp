/*
  ==============================================================================

    HarmonicSlider.cpp
    Created: 10 Nov 2020 4:48:26pm
    Author:  Robin Otterbein

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HarmonicSlider.h"

//==============================================================================
HarmonicSlider::HarmonicSlider()
{
    colour = juce::Colours::black;
    value = 0.5f;
}

HarmonicSlider::~HarmonicSlider()
{
}

void HarmonicSlider::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    
    juce::ColourGradient colourGradient = juce::ColourGradient::vertical(juce::Colours::aquamarine, juce::Colours::royalblue, rectangle);
    g.setGradientFill(colourGradient);
    g.fillRect(rectangle);
}

void HarmonicSlider::resized()
{
    DBG(value);
    rectangle = juce::Rectangle<int>(0, getHeight()*value, getWidth(), getHeight()*(1-value)+1);
}

void HarmonicSlider::setValue(float newValue)
{
    value = newValue;
    
    if (value > 1.0f)
        value = 1.0f;
    
    if (value < 0.0f)
        value = 0.0f;
    
    repaint();
    resized();
}
