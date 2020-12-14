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
    ModulationComponent(juce::AudioProcessorValueTreeState&);
    ~ModulationComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::AudioProcessorValueTreeState& valueTreeState;

    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    juce::ImageButton onoffButton;
    std::unique_ptr<ButtonAttachment> onoffAttachment;

    juce::Label nameLabel;
    juce::Label onoffLabel;
    juce::Slider amountSlider;
    juce::Label amountLabel;
    std::unique_ptr <SliderAttachment> amountAttachment;

    juce::Slider rateSlider;
    juce::Label rateLabel;
    std::unique_ptr <SliderAttachment> rateAttachment;

    juce::Slider delaySlider;
    juce::Label delayLabel;
    std::unique_ptr <SliderAttachment> delayAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModulationComponent)
};

