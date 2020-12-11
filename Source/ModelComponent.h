/*
  ==============================================================================

    ModelComponent.h
    Created: 7 Nov 2020 1:55:54am
    Author:  Robin Otterbein

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ModelComponent  : public juce::Component
{
public:
    ModelComponent(juce::AudioProcessorValueTreeState&);
    ~ModelComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void updateModelState(juce::Button* button);

private:
    juce::AudioProcessorValueTreeState& valueTreeState;
	typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

    juce::ImageButton onoffButton;
    juce::Label nameLabel;
    juce::Label onoffLabel;

    juce::ImageButton violinButton;
    juce::Label violinLabel;
	std::unique_ptr<ButtonAttachment> violinAttachment;

    juce::ImageButton fluteButton;
    juce::Label fluteLabel;
	std::unique_ptr<ButtonAttachment> fluteAttachment;

    juce::ImageButton saxophoneButton;
    juce::Label saxophoneLabel;
	std::unique_ptr<ButtonAttachment> saxophoneAttachment;

    juce::ImageButton trumpetButton;
    juce::Label trumpetLabel;
	std::unique_ptr<ButtonAttachment> trumpetAttachment;

    juce::ImageButton extra1Button;
    juce::Label extra1Label;
    juce::ImageButton extra2Button;
    juce::Label extra2Label;
    juce::ImageButton extra3Button;
    juce::Label extra3Label;
    juce::ImageButton extra4Button;
    juce::Label extra4Label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModelComponent)
};
