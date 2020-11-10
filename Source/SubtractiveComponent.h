/*
  ==============================================================================

    SubtractiveComponent.h
    Created: 7 Nov 2020 2:09:03am
    Author:  Robin Otterbein

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SubtractiveComponent  : public juce::Component
{
public:
    SubtractiveComponent();
    ~SubtractiveComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SubtractiveComponent)
};
