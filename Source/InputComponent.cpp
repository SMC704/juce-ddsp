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
InputComponent::InputComponent(juce::AudioProcessorValueTreeState& vts)
    : valueTreeState(vts)
{
    float fontDim = 15.0f;
    
    addAndMakeVisible(nameLabel);
    nameLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    nameLabel.setJustificationType(juce::Justification::topLeft);
    nameLabel.setText("Input", juce::NotificationType::dontSendNotification);
    nameLabel.setFont(20.0f);
    
    addAndMakeVisible(midiLabel);
    midiLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    midiLabel.setJustificationType(juce::Justification::topLeft);
    midiLabel.setText("MIDI", juce::NotificationType::dontSendNotification);
    midiLabel.setFont(fontDim);
    
    addAndMakeVisible(audioLabel);
    audioLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    audioLabel.setJustificationType(juce::Justification::topLeft);
    audioLabel.setText("Audio", juce::NotificationType::dontSendNotification);
    audioLabel.setFont(fontDim);
    
    addAndMakeVisible(inputSwitch);
    inputSwitch.setBounds(0, 0, 50, 50);
    inputSwitch.setClickingTogglesState(true);
    inputSwitch.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::switch_left_png, BinaryData::switch_left_pngSize), 1.0f, {},
        {}, 1.0f, {},
        juce::ImageFileFormat::loadFrom(BinaryData::switch_right_png, BinaryData::switch_right_pngSize), 1.0f, {},
        0.0f);
    //inputSwitch.setToggleState(false, NULL);
    inputSwitch.onClick = [this] { updateInputState(&inputSwitch); };

    inputSwitchAttachment.reset(new ButtonAttachment(valueTreeState, "inputIsLine", inputSwitch));

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

    grid.items = {

        juce::GridItem(nameLabel).withSize(100.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin(10.0f))
            .withArea(1, 1),
        
        juce::GridItem(midiLabel).withSize(100.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(-3.0f, -75.0f, 0.0f, 0.0f))
            .withArea(2, 1),
        
        juce::GridItem(audioLabel).withSize(100.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(-3.0f, -45.0f, 0.0f, 0.0f))
            .withArea(2, 2),
        
        juce::GridItem(inputSwitch).withSize(40.0f, 40.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin(-15.0f, 0, 0 , -51.0f))
            .withArea(2, 2),

    };

    grid.performLayout(getLocalBounds());
}

void InputComponent::updateInputState(juce::Button *button)
{
    if(button == &inputSwitch && inputSwitch.getToggleState() == true)
    {
        DBG("Audio Mode activated");
    }
    else if(button == &inputSwitch && inputSwitch.getToggleState() == false)
    {
        DBG("MIDI Mode activated");
    }
}
