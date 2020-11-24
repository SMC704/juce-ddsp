/*
  ==============================================================================

    ReverbComponent.h
    Created: 7 Nov 2020 2:13:37am
    Author:  Robin Otterbein

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ReverbComponent  : public juce::Component
{
public:
    ReverbComponent();
    ~ReverbComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::ToggleButton onoffButton;
    juce::Label nameLabel;
    juce::Label onoffLabel;
    juce::Slider drywetSlider;
    juce::Label drywetLabel;
    juce::Slider sizeSlider;
    juce::Label sizeLabel;
    juce::Slider glowSlider;
    juce::Label glowLabel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
