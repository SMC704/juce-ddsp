/*
  ==============================================================================

    SubtractiveComponent.cpp
    Created: 7 Nov 2020 2:09:03am
    Author:  Robin Otterbein

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SubtractiveComponent.h"

//==============================================================================
SubtractiveComponent::SubtractiveComponent()
{

}

SubtractiveComponent::~SubtractiveComponent()
{
}

void SubtractiveComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.drawRect (getLocalBounds(), 3);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Subtractive", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void SubtractiveComponent::resized()
{

}
