/*
  ==============================================================================

    InputComponent.h
    Created: 6 Nov 2020 5:23:11pm
    Author:  Robin Otterbein

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class InputComponent  : public juce::Component
{
public:
    InputComponent();
    ~InputComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Label nameLabel;
    juce::TextButton midiButton;
    juce::TextButton lineButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InputComponent)
};
