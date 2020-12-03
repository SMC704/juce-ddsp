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
    ModelComponent();
    ~ModelComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::ImageButton onoffButton;
    juce::Label nameLabel;
    juce::Label onoffLabel;
    juce::ImageButton violinButton;
    juce::Label violinLabel;
    juce::ImageButton fluteButton;
    juce::Label fluteLabel;
    juce::ImageButton saxophoneButton;
    juce::Label saxophoneLabel;
    juce::ImageButton trumpetButton;
    juce::Label trumpetLabel;
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
