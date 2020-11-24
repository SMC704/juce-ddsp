/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DdspsynthAudioProcessorEditor::DdspsynthAudioProcessorEditor (DdspsynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName("Avenir Next");

    backgroundTexture = backgroundTexture.rescaled(900, 600);
    addAndMakeVisible(mainComponent);
    mainComponent.setBounds(20, 20, 860, 560);
    setSize (900, 600);
    
    mainComponent.setLookAndFeel(&otherLookAndFeel);
}

DdspsynthAudioProcessorEditor::~DdspsynthAudioProcessorEditor()
{
    mainComponent.setLookAndFeel(nullptr);
}

//==============================================================================
void DdspsynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    
    g.drawImageAt(backgroundTexture, 0, 0);
    
}

void DdspsynthAudioProcessorEditor::resized()
{
    
}
