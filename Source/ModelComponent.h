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
    juce::TextButton violinButton;
    juce::Label violinLabel;
    juce::TextButton fluteButton;
    juce::Label fluteLabel;
    juce::TextButton saxophoneButton;
    juce::Label saxophoneLabel;
    juce::TextButton trumpetButton;
    juce::Label trumpetLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModelComponent)
};
