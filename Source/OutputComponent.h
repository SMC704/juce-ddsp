/*
  ==============================================================================

    OutputComponent.h
    Created: 7 Nov 2020 2:09:43am
    Author:  Robin Otterbein

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OutputComponent  : public juce::Component
{
public:
    OutputComponent();
    ~OutputComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputComponent)
};
