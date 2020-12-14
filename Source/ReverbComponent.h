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
    ReverbComponent(juce::AudioProcessorValueTreeState&);
    ~ReverbComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::AudioProcessorValueTreeState& valueTreeState;

    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    juce::ImageButton onoffButton;
    juce::Label nameLabel;
    juce::Label onoffLabel;
    std::unique_ptr<ButtonAttachment> onoffAttachment;

    juce::Slider drywetSlider;
    juce::Label drywetLabel;
    std::unique_ptr <SliderAttachment> drywetAttachment;

    juce::Slider sizeSlider;
    juce::Label sizeLabel;
    std::unique_ptr <SliderAttachment> sizeAttachment;

    juce::Slider glowSlider;
    juce::Label glowLabel;
    std::unique_ptr <SliderAttachment> glowAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
