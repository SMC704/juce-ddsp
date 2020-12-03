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

    addAndMakeVisible(nameLabel);
    nameLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    nameLabel.setJustificationType(juce::Justification::topLeft);
    nameLabel.setText("Model", juce::NotificationType::dontSendNotification);
    nameLabel.setFont(20.0f);

    addAndMakeVisible(onoffButton);
    onoffButton.setBounds(0, 0, 50, 50);
    //onoffButton.addListener(this);
    onoffButton.setClickingTogglesState(true);
    onoffButton.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::power_png, BinaryData::power_pngSize), {}, juce::Colour::fromRGB(100, 100, 100), //Normal
        juce::ImageFileFormat::loadFrom(BinaryData::power_png, BinaryData::power_pngSize), {}, juce::Colour::fromRGB(200, 200, 200), //Over
        juce::ImageFileFormat::loadFrom(BinaryData::power_png, BinaryData::power_pngSize), {}, juce::Colour::fromRGB(255, 255, 255), //Down
        0.0f);
    onoffButton.setClickingTogglesState(true);

    addAndMakeVisible(onoffLabel);
    onoffLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    onoffLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(violinButton);
    violinButton.setButtonText("Violin");
    violinButton.setBounds(0, 0, 50, 50);
    violinButton.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::violin_png, BinaryData::violin_pngSize),
        0.85f, {}, {}, 0.75f, {}, {}, 1.0f, {}, 0.0f);

    addAndMakeVisible(violinLabel);
    violinLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    violinLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(fluteButton);
    fluteButton.setButtonText("Flute");
    fluteButton.setBounds(0, 0, 50, 50);
    fluteButton.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::flute_png, BinaryData::flute_pngSize),
        0.85f, {}, {}, 0.75f, {}, {}, 1.0f, {}, 0.0f);

    addAndMakeVisible(fluteLabel);
    fluteLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    fluteLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(saxophoneButton);
    saxophoneButton.setButtonText("Sax");
    saxophoneButton.setBounds(0, 0, 50, 50);
    saxophoneButton.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::saxophone_png, BinaryData::saxophone_pngSize),
        0.85f, {}, {}, 0.75f, {}, {}, 1.0f, {}, 0.0f);

    addAndMakeVisible(saxophoneLabel);
    saxophoneLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    saxophoneLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(trumpetButton);
    trumpetButton.setButtonText("Trumpet");
    trumpetButton.setBounds(0, 0, 50, 50);
    trumpetButton.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::trumpet_png, BinaryData::trumpet_pngSize),
        0.85f, {}, {}, 0.75f, {}, {}, 1.0f, {}, 0.0f);

    addAndMakeVisible(trumpetLabel);
    trumpetLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    trumpetLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(extra1Button);
    extra1Button.setButtonText("Extra 1");
    extra1Button.setBounds(0, 0, 50, 50);
    extra1Button.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::placeholder_png, BinaryData::placeholder_pngSize),
        0.85f, {}, {}, 0.75f, {}, {}, 1.0f, {}, 0.0f);

    addAndMakeVisible(extra1Label);
    extra1Label.setColour(juce::Label::textColourId, juce::Colours::white);
    extra1Label.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(extra2Button);
    extra2Button.setButtonText("Extra 2");
    extra2Button.setBounds(0, 0, 50, 50);
    extra2Button.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::placeholder_png, BinaryData::placeholder_pngSize),
        0.85f, {}, {}, 0.75f, {}, {}, 1.0f, {}, 0.0f);

    addAndMakeVisible(extra2Label);
    extra2Label.setColour(juce::Label::textColourId, juce::Colours::white);
    extra2Label.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(extra3Button);
    extra3Button.setButtonText("Extra 3");
    extra3Button.setBounds(0, 0, 50, 50);
    extra3Button.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::placeholder_png, BinaryData::placeholder_pngSize),
        0.85f, {}, {}, 0.75f, {}, {}, 1.0f, {}, 0.0f);

    addAndMakeVisible(extra3Label);
    extra3Label.setColour(juce::Label::textColourId, juce::Colours::white);
    extra3Label.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(extra4Button);
    extra4Button.setButtonText("Extra 4");
    extra4Button.setBounds(0, 0, 50, 50);
    extra4Button.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::placeholder_png, BinaryData::placeholder_pngSize),
        0.85f, {}, {}, 0.75f, {}, {}, 1.0f, {}, 0.0f);

    addAndMakeVisible(extra4Label);
    extra4Label.setColour(juce::Label::textColourId, juce::Colours::white);
    extra4Label.setJustificationType(juce::Justification::centred);

}

ModelComponent::~ModelComponent()
{
}

void ModelComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.drawRect (getLocalBounds(), 3);   // draw an outline around the component

    /*
    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Model", getLocalBounds(),
                juce::Justification::topLeft, true);   // draw some placeholder text
     */
}

void ModelComponent::resized()
{
    juce::Grid grid;
     
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    //5 rows
    grid.templateRows = {
        Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)),
        Track(Fr(1))
    };
    //2 columns
    grid.templateColumns = {
        Track(Fr(1)), Track(Fr(1))
    };
    
    grid.rowGap = juce::Grid::Px(10.0f);
    grid.columnGap = juce::Grid::Px(10.0f);

    float buttonDim = 65.0f;

    grid.items = {

        juce::GridItem(nameLabel).withSize(60.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin(10.0f))
            .withArea(1, 1),

        juce::GridItem(onoffButton).withSize(17.0f, 17.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(10.0f))
            .withArea(1, 2),

        juce::GridItem(violinButton).withSize(buttonDim, buttonDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(-20.f, 0, 0, 0))
            .withArea(2, 1),

        juce::GridItem(fluteButton).withSize(buttonDim, buttonDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin(-20.f, 0, 0, 0))
            .withArea(2, 2),

        juce::GridItem(saxophoneButton).withSize(buttonDim, buttonDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(-20.f, 0, 0, 0))
            .withArea(3, 1),

        juce::GridItem(trumpetButton).withSize(buttonDim, buttonDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin(-20.f, 0, 0, 0))
            .withArea(3,2),

        juce::GridItem(extra1Button).withSize(buttonDim, buttonDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(-20.f, 0, 0, 0))
            .withArea(4, 1),

        juce::GridItem(extra2Button).withSize(buttonDim, buttonDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin(-20.f, 0, 0, 0))
            .withArea(4,2),

        juce::GridItem(extra3Button).withSize(buttonDim, buttonDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(-20.f, 0, 0, 0))
            .withArea(5,1),

        juce::GridItem(extra4Button).withSize(buttonDim, buttonDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin(-20.f, 0, 0, 0))
            .withArea(5,2),
    };

    grid.performLayout (getLocalBounds());
}
