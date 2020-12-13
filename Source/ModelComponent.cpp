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
    violinButton.setTooltip("Violin");

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

    addAndMakeVisible(synthbassButton);
    synthbassButton.setButtonText("Synthbass");
    synthbassButton.setBounds(0, 0, 50, 50);
    synthbassButton.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::synthbass_png, BinaryData::synthbass_pngSize),
        0.65f, {}, {}, 0.85f, {}, {}, 1.0f, {}, 0.0f);
    synthbassButton.setRadioGroupId(1001);
    synthbassButton.setClickingTogglesState(true);
    synthbassButton.onClick = [this] { updateModelState(&synthbassButton); };

    addAndMakeVisible(synthbassLabel);
    synthbassLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    synthbassLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(dulcimerButton);
    dulcimerButton.setButtonText("Dulcimer");
    dulcimerButton.setBounds(0, 0, 50, 50);
    dulcimerButton.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::dulcimer_png, BinaryData::dulcimer_pngSize),
        0.65f, {}, {}, 0.85f, {}, {}, 1.0f, {}, 0.0f);
    dulcimerButton.setRadioGroupId(1001);
    dulcimerButton.setClickingTogglesState(true);
    dulcimerButton.onClick = [this] { updateModelState(&dulcimerButton); };

    addAndMakeVisible(dulcimerLabel);
    dulcimerLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    dulcimerLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(handpanButton);
    handpanButton.setButtonText("Handpan");
    handpanButton.setBounds(0, 0, 50, 50);
    handpanButton.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::handpan_png, BinaryData::handpan_pngSize),
        0.65f, {}, {}, 0.85f, {}, {}, 1.0f, {}, 0.0f);
    handpanButton.setRadioGroupId(1001);
    handpanButton.setClickingTogglesState(true);
    handpanButton.onClick = [this] { updateModelState(&handpanButton); };

    addAndMakeVisible(handpanLabel);
    handpanLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    handpanLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(birdsButton);
    birdsButton.setButtonText("Birds");
    birdsButton.setBounds(0, 0, 50, 50);
    birdsButton.setImages(false, true, false,
        juce::ImageFileFormat::loadFrom(BinaryData::birds_png, BinaryData::birds_pngSize),
        0.65f, {}, {}, 0.85f, {}, {}, 1.0f, {}, 0.0f);
    birdsButton.setRadioGroupId(1001);
    birdsButton.setClickingTogglesState(true);
    birdsButton.onClick = [this] { updateModelState(&birdsButton); };

    addAndMakeVisible(birdsLabel);
    birdsLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    birdsLabel.setJustificationType(juce::Justification::centred);

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

        juce::GridItem(synthbassButton).withSize(buttonDim, buttonDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(-20.f, 0, 0, 0))
            .withArea(4, 1),

        juce::GridItem(dulcimerButton).withSize(buttonDim, buttonDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin(-20.f, 0, 0, 0))
            .withArea(4,2),

        juce::GridItem(handpanButton).withSize(buttonDim, buttonDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(-20.f, 0, 0, 0))
            .withArea(5,1),

        juce::GridItem(birdsButton).withSize(buttonDim, buttonDim)
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
    else if(button == &synthbassButton && synthbassButton.getToggleState() == true)
    {
        DBG("synthbass model activated");
        *param = 4;
    }
    else if(button == &dulcimerButton && dulcimerButton.getToggleState() == true)
    {
        DBG("dulcimer model activated");
        *param = 5;
    }
    else if(button == &handpanButton && handpanButton.getToggleState() == true)
    {
        DBG("handpan model activated");
        *param = 6;
    }
    else if(button == &birdsButton && birdsButton.getToggleState() == true)
    {
        DBG("extra4 model activated");
        *param = 7;
    }
}
