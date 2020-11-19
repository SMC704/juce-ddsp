/*
  ==============================================================================

    InputComponent.cpp
    Created: 6 Nov 2020 5:23:11pm
    Author:  Robin Otterbein

  ==============================================================================
*/

#include <JuceHeader.h>
#include "InputComponent.h"

//==============================================================================
InputComponent::InputComponent()
{
    addAndMakeVisible(nameLabel);
    nameLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    nameLabel.setJustificationType(juce::Justification::topLeft);
    nameLabel.setText("Input", juce::NotificationType::dontSendNotification);
    nameLabel.setFont(20.0f);

    addAndMakeVisible(midiButton);
    midiButton.setButtonText("MIDI");
    midiButton.setBounds(0, 0, 50, 50);

    addAndMakeVisible(lineButton);
    lineButton.setButtonText("Line");
    lineButton.setBounds(0, 0, 50, 50);
}

InputComponent::~InputComponent()
{
}

void InputComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.drawRect (getLocalBounds(), 3);   // draw an outline around the component

    /*
    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Input", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text*/
}

void InputComponent::resized()
{
    juce::Grid grid;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    //2 rows
    grid.templateRows = {
        Track(Fr(1)), Track(Fr(1))
    };
    //2 columns
    grid.templateColumns = {
        Track(Fr(1)), Track(Fr(1))
    };

    grid.rowGap = juce::Grid::Px(10.0f);
    grid.columnGap = juce::Grid::Px(10.0f);

    float buttonDimHeigth = 25.0f;
    float buttonDimWidth = 60.0f; 

    grid.items = {

        juce::GridItem(nameLabel).withSize(100.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin::Margin(10.0f))
            .withArea(1, 1),

         juce::GridItem(midiButton).withSize(buttonDimWidth, buttonDimHeigth)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin::Margin(-17.0f, 0, 0 , -35.0f))
            .withArea(2, 2),

        juce::GridItem(lineButton).withSize(buttonDimWidth, buttonDimHeigth)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin::Margin(-17.0f, 0, 0 , 20.0f))
            .withArea(2, 2),

    };

    grid.performLayout(getLocalBounds());
}
