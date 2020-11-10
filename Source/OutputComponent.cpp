/*
  ==============================================================================

    OutputComponent.cpp
    Created: 7 Nov 2020 2:09:43am
    Author:  Robin Otterbein

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OutputComponent.h"

//==============================================================================
OutputComponent::OutputComponent()
{

}

OutputComponent::~OutputComponent()
{
}

void OutputComponent::paint (juce::Graphics& g)
{

    g.setColour (juce::Colours::white);
    g.drawRect (getLocalBounds(), 3);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Output", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void OutputComponent::resized()
{
    
}
