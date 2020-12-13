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

    juce::ImageButton synthbassButton;
    juce::Label synthbassLabel;
    std::unique_ptr<ButtonAttachment> synthbassAttachment;
    
    juce::ImageButton dulcimerButton;
    juce::Label dulcimerLabel;
    std::unique_ptr<ButtonAttachment> dulcimerAttachment;
    
    juce::ImageButton handpanButton;
    juce::Label handpanLabel;
    std::unique_ptr<ButtonAttachment> handpanAttachment;
    
    juce::ImageButton birdsButton;
    juce::Label birdsLabel;
    std::unique_ptr<ButtonAttachment> birdsAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModelComponent)
};
