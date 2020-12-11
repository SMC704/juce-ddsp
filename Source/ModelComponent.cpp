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
ModelComponent::ModelComponent(juce::AudioProcessorValueTreeState& vts)
    : valueTreeState(vts)
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
        juce::ImageFileFormat::loadFrom(BinaryData::power_png, BinaryData::power_pngSize), {}, juce::Colour::fromRGB(255, 255, 255), //Normal
        juce::ImageFileFormat::loadFrom(BinaryData::power_png, BinaryData::power_pngSize), {}, juce::Colour::fromRGB(200, 200, 200), //Over
        juce::ImageFileFormat::loadFrom(BinaryData::power_png, BinaryData::power_pngSize), {}, juce::Colour::fromRGB(100, 100, 100), //Down
        0.0f);
    onoffButton.setToggleState(true, NULL);
    onoffButton.setRadioGroupId(1001);
    onoffButton.onClick = [this] { updateModelState(&onoffButton); };

    addAndMakeVisible(onoffLabel);
    onoffLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    onoffLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(violinButton);
    violinButton.setButtonText("Violin");
    violinButton.setBounds(0, 0, 50, 50);
    violinButton.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::violin_png, BinaryData::violin_pngSize),
        0.65f, {}, {}, 0.85f, {}, {}, 1.0f, {}, 0.0f);
    violinButton.setRadioGroupId(1001);
    violinButton.setClickingTogglesState(true);
    violinButton.onClick = [this] { updateModelState(&violinButton); };

    addAndMakeVisible(violinLabel);
    violinLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    violinLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(fluteButton);
    fluteButton.setButtonText("Flute");
    fluteButton.setBounds(0, 0, 50, 50);
    fluteButton.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::flute_png, BinaryData::flute_pngSize),
        0.65f, {}, {}, 0.85f, {}, {}, 1.0f, {}, 0.0f);
    fluteButton.setRadioGroupId(1001);
    fluteButton.setClickingTogglesState(true);
    fluteButton.onClick = [this] { updateModelState(&fluteButton); };

    addAndMakeVisible(fluteLabel);
    fluteLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    fluteLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(saxophoneButton);
    saxophoneButton.setButtonText("Sax");
    saxophoneButton.setBounds(0, 0, 50, 50);
    saxophoneButton.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::saxophone_png, BinaryData::saxophone_pngSize),
        0.65f, {}, {}, 0.85f, {}, {}, 1.0f, {}, 0.0f);
    saxophoneButton.setRadioGroupId(1001);
    saxophoneButton.setClickingTogglesState(true);
    saxophoneButton.onClick = [this] { updateModelState(&saxophoneButton); };

    addAndMakeVisible(saxophoneLabel);
    saxophoneLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    saxophoneLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(trumpetButton);
    trumpetButton.setButtonText("Trumpet");
    trumpetButton.setBounds(0, 0, 50, 50);
    trumpetButton.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::trumpet_png, BinaryData::trumpet_pngSize),
        0.65f, {}, {}, 0.85f, {}, {}, 1.0f, {}, 0.0f);
    trumpetButton.setRadioGroupId(1001);
    trumpetButton.setClickingTogglesState(true);
    trumpetButton.onClick = [this] { updateModelState(&trumpetButton); };

    addAndMakeVisible(trumpetLabel);
    trumpetLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    trumpetLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(extra1Button);
    extra1Button.setButtonText("Extra 1");
    extra1Button.setBounds(0, 0, 50, 50);
    extra1Button.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::placeholder_png, BinaryData::placeholder_pngSize),
        0.65f, {}, {}, 0.85f, {}, {}, 1.0f, {}, 0.0f);
    extra1Button.setRadioGroupId(1001);
    extra1Button.setClickingTogglesState(true);
    extra1Button.onClick = [this] { updateModelState(&extra1Button); };

    addAndMakeVisible(extra1Label);
    extra1Label.setColour(juce::Label::textColourId, juce::Colours::white);
    extra1Label.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(extra2Button);
    extra2Button.setButtonText("Extra 2");
    extra2Button.setBounds(0, 0, 50, 50);
    extra2Button.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::placeholder_png, BinaryData::placeholder_pngSize),
        0.65f, {}, {}, 0.85f, {}, {}, 1.0f, {}, 0.0f);
    extra2Button.setRadioGroupId(1001);
    extra2Button.setClickingTogglesState(true);
    extra2Button.onClick = [this] { updateModelState(&extra2Button); };

    addAndMakeVisible(extra2Label);
    extra2Label.setColour(juce::Label::textColourId, juce::Colours::white);
    extra2Label.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(extra3Button);
    extra3Button.setButtonText("Extra 3");
    extra3Button.setBounds(0, 0, 50, 50);
    extra3Button.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::placeholder_png, BinaryData::placeholder_pngSize),
        0.65f, {}, {}, 0.85f, {}, {}, 1.0f, {}, 0.0f);
    extra3Button.setRadioGroupId(1001);
    extra3Button.setClickingTogglesState(true);
    extra3Button.onClick = [this] { updateModelState(&extra3Button); };

    addAndMakeVisible(extra3Label);
    extra3Label.setColour(juce::Label::textColourId, juce::Colours::white);
    extra3Label.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(extra4Button);
    extra4Button.setButtonText("Extra 4");
    extra4Button.setBounds(0, 0, 50, 50);
    extra4Button.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::placeholder_png, BinaryData::placeholder_pngSize),
        0.65f, {}, {}, 0.85f, {}, {}, 1.0f, {}, 0.0f);
    extra4Button.setRadioGroupId(1001);
    extra4Button.setClickingTogglesState(true);
    extra4Button.onClick = [this] { updateModelState(&extra4Button); };

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

void ModelComponent::updateModelState(juce::Button *button)
{
	auto param = (juce::AudioParameterChoice*) valueTreeState.getParameter("modelSelect");

    if(button == &onoffButton && onoffButton.getToggleState() == true)
    {
        DBG("no model activated");
    }
    else if(button == &violinButton && violinButton.getToggleState() == true)
    {
        DBG("violin model activated");
		*param = 0;
    }
    else if(button == &fluteButton && fluteButton.getToggleState() == true)
    {
        DBG("flute model activated");
		*param = 1;
    }
    else if(button == &saxophoneButton && saxophoneButton.getToggleState() == true)
    {
        DBG("saxophone model activated");
		*param = 2;
    }
    else if(button == &trumpetButton && trumpetButton.getToggleState() == true)
    {
        DBG("trumpet model activated");
		*param = 3;
    }
    else if(button == &extra1Button && extra1Button.getToggleState() == true)
    {
        DBG("extra1 model activated");
    }
    else if(button == &extra2Button && extra2Button.getToggleState() == true)
    {
        DBG("extra2 model activated");
    }
    else if(button == &extra3Button && extra3Button.getToggleState() == true)
    {
        DBG("extra3 model activated");
    }
    else if(button == &extra4Button && extra4Button.getToggleState() == true)
    {
        DBG("extra4 model activated");
    }
}
