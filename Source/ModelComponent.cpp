/*
  ==============================================================================

    ModelComponent.cpp
    Created: 7 Nov 2020 1:55:54am
    Author:  Robin Otterbein

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ModelComponent.h"

//==============================================================================
ModelComponent::ModelComponent()
{
    addAndMakeVisible(violinButton);
    violinButton.setButtonText ("Violin");
    violinButton.setBounds(0, 0, 50, 50);
    
    addAndMakeVisible (violinLabel);
    violinLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    violinLabel.setJustificationType (juce::Justification::centred);
    
    addAndMakeVisible(fluteButton);
    fluteButton.setButtonText ("Flute");
    fluteButton.setBounds(0, 0, 50, 50);
    
    addAndMakeVisible (fluteLabel);
    fluteLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    fluteLabel.setJustificationType (juce::Justification::centred);
    
    addAndMakeVisible(saxophoneButton);
    saxophoneButton.setButtonText ("Sax");
    saxophoneButton.setBounds(0, 0, 50, 50);
    
    addAndMakeVisible (saxophoneLabel);
    saxophoneLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    saxophoneLabel.setJustificationType (juce::Justification::centred);
    
    addAndMakeVisible(trumpetButton);
    trumpetButton.setButtonText ("Trumpet");
    trumpetButton.setBounds(0, 0, 50, 50);
    
    addAndMakeVisible (trumpetLabel);
    trumpetLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    trumpetLabel.setJustificationType (juce::Justification::centred);
}

ModelComponent::~ModelComponent()
{
}

void ModelComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.drawRect (getLocalBounds(), 3);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Model", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void ModelComponent::resized()
{
    juce::Grid grid;
     
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows    = {
        Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1)),
        Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1)),
        Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1))
    };
    grid.templateColumns = {
        Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1)),
        Track (Fr (1)), Track (Fr (1))
    };
    
    grid.rowGap = juce::Grid::Px(10.0f);
    grid.columnGap = juce::Grid::Px(10.0f);

    grid.items = {
        juce::GridItem (violinButton).withArea(2, 2, 4, 4),
        juce::GridItem (fluteButton).withArea(2, 4, 4, 6),
        juce::GridItem (saxophoneButton).withArea(4, 2, 6, 4),
        juce::GridItem (trumpetButton).withArea(4, 4, 6, 6)
    };

    grid.performLayout (getLocalBounds());
}
