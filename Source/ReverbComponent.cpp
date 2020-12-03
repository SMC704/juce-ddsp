/*
  ==============================================================================

    ReverbComponent.cpp
    Created: 7 Nov 2020 2:13:37am
    Author:  Robin Otterbein

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent()
{
    float fontDim = 15.0f;

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
    onoffButton.setToggleState(true, NULL);

    addAndMakeVisible(onoffLabel);
    onoffLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    onoffLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(nameLabel);
    nameLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    nameLabel.setJustificationType(juce::Justification::topLeft);
    nameLabel.setText("Reverb", juce::NotificationType::dontSendNotification);
    nameLabel.setFont(20.0f);

    drywetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    drywetSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    drywetSlider.setRange(0.0f, 10.0f, 0.1f);
    drywetSlider.setValue(5.0f);
    addAndMakeVisible(drywetSlider);
    drywetSlider.setBounds(0, 0, 100, 100);

    addAndMakeVisible(drywetLabel);
    drywetLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    drywetLabel.setJustificationType(juce::Justification::topLeft);
    drywetLabel.setText("Dry/Wet", juce::NotificationType::dontSendNotification);
    drywetLabel.setFont(fontDim);

    sizeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sizeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    sizeSlider.setRange(0.0f, 10.0f, 0.1f);
    sizeSlider.setValue(5.0f);
    addAndMakeVisible(sizeSlider);
    sizeSlider.setBounds(0, 0, 100, 100);

    addAndMakeVisible(sizeLabel);
    sizeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    sizeLabel.setJustificationType(juce::Justification::topLeft);
    sizeLabel.setText("Size", juce::NotificationType::dontSendNotification);
    sizeLabel.setFont(fontDim);

    glowSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    glowSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    glowSlider.setRange(0.0f, 10.0f, 0.1f);
    glowSlider.setValue(5.0f);
    addAndMakeVisible(glowSlider);
    glowSlider.setBounds(0, 0, 100, 100);

    addAndMakeVisible(glowLabel);
    glowLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    glowLabel.setJustificationType(juce::Justification::topLeft);
    glowLabel.setText("Glow", juce::NotificationType::dontSendNotification);
    glowLabel.setFont(fontDim);

}

ReverbComponent::~ReverbComponent()
{
}

void ReverbComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.drawRect (getLocalBounds(), 3);   // draw an outline around the component

    /*
    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Reverb", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
    */
}

void ReverbComponent::resized()
{

    juce::Grid grid;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    //7 rows
    grid.templateRows = {
        Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)),
        Track(Fr(1)), Track(Fr(1)), Track(Fr(1))
    };
    //3 column
    grid.templateColumns = {
        Track(Fr(1)), Track(Fr(1)), Track(Fr(1))
    };

    grid.rowGap = juce::Grid::Px(10.0f);
    grid.columnGap = juce::Grid::Px(10.0f);

    float sliderDim = 50.0f;

    grid.items = {

        juce::GridItem(nameLabel).withSize(100.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin(10.0f))
            .withArea(1, 1),

        juce::GridItem(onoffButton).withSize(17.0f, 17.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(10.0f, 10.0f, 10.0f, 0.0f))
            .withArea(1, 3),

        juce::GridItem(drywetSlider).withSize(70.0f, 70.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 0, 0))
            .withArea(2, 2),

        juce::GridItem(drywetLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::end)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 0, 5.0f))
            .withArea(5, 2),

        juce::GridItem(sizeSlider).withSize(sliderDim, sliderDim)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin(0.0f, 0.0f, 10.0f, 10.0f))
            .withArea(6, 1),

        juce::GridItem(sizeLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 0, 18.0f))
            .withArea(7, 1),

        juce::GridItem(glowSlider).withSize(sliderDim, sliderDim)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(0.0f, 10.0f, 10.0f, 0))
            .withArea(6, 3),

        juce::GridItem(glowLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin(10.0f, 6.0f, 0, 1.0f))
            .withArea(7, 3),
    };

    grid.performLayout(getLocalBounds());
}
