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

    juce::ToggleButton onoffButton;
    juce::Label nameLabel;
    juce::Label onoffLabel;
    juce::Slider ampSlider;
    juce::Label ampLabel;
    juce::Label lfoLabel;
    juce::Slider amoutSlider;
    juce::Label amountLabel;
    juce::Slider rateSlider;
    juce::Label rateLabel;
    juce::Slider colourSlider;
    juce::Label colourLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SubtractiveComponent)
};
