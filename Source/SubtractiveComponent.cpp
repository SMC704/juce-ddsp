/*
  ==============================================================================

    SubtractiveComponent.cpp
    Created: 7 Nov 2020 2:09:03am
    Author:  Robin Otterbein

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SubtractiveComponent.h"

//==============================================================================
SubtractiveComponent::SubtractiveComponent()
{
    float fontDim = 15.0f;

    addAndMakeVisible(onoffButton);
    onoffButton.setBounds(0, 0, 50, 50);
    onoffButton.addListener(this);
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

    addAndMakeVisible(nameLabel);
    nameLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    nameLabel.setJustificationType(juce::Justification::topLeft);
    nameLabel.setText("Noise", juce::NotificationType::dontSendNotification);
    nameLabel.setFont(20.0f);

    ampSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ampSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    ampSlider.setPopupDisplayEnabled(true, true, this);
    ampSlider.setTextValueSuffix (" dB");
    ampSlider.setRange(-60.0f, 0.0f, 0.01f);
    ampSlider.setValue(-10.0f);
    addAndMakeVisible(ampSlider);
    ampSlider.setBounds(0, 0, 100, 100);
    ampSlider.addListener(this);
    ampSlider.setDoubleClickReturnValue(true, -10.0f);

    addAndMakeVisible(ampLabel);
    ampLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    ampLabel.setJustificationType(juce::Justification::topLeft);
    ampLabel.setText("Amp", juce::NotificationType::dontSendNotification);
    ampLabel.setFont(fontDim);

    colourSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    colourSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    colourSlider.setPopupDisplayEnabled(true, true, this);
    colourSlider.setTextValueSuffix (" Noise Colour");
    colourSlider.setRange(-1.0f, 1.0f, 0.01f);
    colourSlider.setValue(0.0f);
    addAndMakeVisible(colourSlider);
    colourSlider.setBounds(0, 0, 100, 100);
    colourSlider.addListener(this);
    colourSlider.setDoubleClickReturnValue(true, 0.0f);

    addAndMakeVisible(colourLabel);
    colourLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    colourLabel.setJustificationType(juce::Justification::topLeft);
    colourLabel.setText("Colour", juce::NotificationType::dontSendNotification);

    colourLabel.setFont(fontDim);

}

SubtractiveComponent::~SubtractiveComponent()
{
}

void SubtractiveComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.drawRect (getLocalBounds(), 3);   // draw an outline around the component

    /*
    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Subtractive", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text

    */
}

void SubtractiveComponent::resized()
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

        juce::GridItem(colourSlider).withSize(70.0f, 70.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 0, 0))
            .withArea(2, 2),

        juce::GridItem(colourLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::end)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 0, 12.0f))
            .withArea(5, 2),
        
        juce::GridItem(ampSlider).withSize(sliderDim, sliderDim)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(0.0f, -5.0f, 10.0f, 0))
            .withArea(6, 2),

        juce::GridItem(ampLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 0, 25.0f))
            .withArea(7, 2),
    };


    grid.performLayout(getLocalBounds());
    
}

void SubtractiveComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &colourSlider) {
        noiseColor = colourSlider.getValue();
        if (subtractiveListener != NULL)
            subtractiveListener->onNoiseColorChange(noiseColor);
    }
    
    if (slider == &ampSlider) {
        subAmp = ampSlider.getValue();
        if (subtractiveListener != NULL)
            subtractiveListener->onSubAmpChange(subAmp);
    }
}

void SubtractiveComponent::setSubtractiveListener(SubtractiveListener* subListener)
{
    subtractiveListener = subListener;
    if (subtractiveListener != NULL) {
        subtractiveListener->onNoiseColorChange(noiseColor);
        subtractiveListener->onSubAmpChange(subAmp);
        subtractiveListener->onOnOffSubChange(onOffState);
    }
}

void SubtractiveComponent::buttonClicked(juce::Button* button)
{
    onOffState = button->getToggleState();
    subtractiveListener->onOnOffSubChange(onOffState);
}