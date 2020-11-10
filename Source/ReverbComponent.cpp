/*
  ==============================================================================

    ReverbComponent.cpp
    Created: 7 Nov 2020 2:13:37am
    Author:  Robin Otterbein

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent()
{

}

ReverbComponent::~ReverbComponent()
{
}

void ReverbComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.drawRect (getLocalBounds(), 3);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Reverb", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void ReverbComponent::resized()
{

}
