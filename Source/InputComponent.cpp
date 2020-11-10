/*
  ==============================================================================

    InputComponent.cpp
    Created: 6 Nov 2020 5:23:11pm
    Author:  Robin Otterbein

  ==============================================================================
*/

#include <JuceHeader.h>
#include "InputComponent.h"

//==============================================================================
InputComponent::InputComponent()
{

}

InputComponent::~InputComponent()
{
}

void InputComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.drawRect (getLocalBounds(), 3);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Input", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void InputComponent::resized()
{
    
}
