/*
  ==============================================================================

    ModulationComponent.h
    Created: 2 Dec 2020 2:55:18pm
    Author:  Francesco Ganis

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================

class ModulationComponent : public juce::Component
{
public:
    ModulationComponent();
    ~ModulationComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:

    juce::ImageButton onoffButton;
    juce::Label nameLabel;
    juce::Label onoffLabel;
    juce::Slider amoutSlider;
    juce::Label amountLabel;
    juce::Slider rateSlider;
    juce::Label rateLabel;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModulationComponent)
};

