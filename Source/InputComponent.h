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
    InputComponent(juce::AudioProcessorValueTreeState&);
    ~InputComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void updateInputState(juce::Button *button);

private:

    juce::AudioProcessorValueTreeState& valueTreeState;

    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

    juce::Label nameLabel;
    juce::Label midiLabel;
    juce::Label audioLabel;
    juce::ImageButton inputSwitch;
    std::unique_ptr <ButtonAttachment> inputSwitchAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InputComponent)
};
