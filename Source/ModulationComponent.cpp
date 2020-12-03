/*
  ==============================================================================

    ModulationComponent.cpp
    Created: 2 Dec 2020 2:55:18pm
    Author:  Francesco Ganis

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ModulationComponent.h"

//==============================================================================
ModulationComponent::ModulationComponent()
{
    float fontDim = 15.0f;
    
    addAndMakeVisible(onoffButton);
    onoffButton.setBounds(0, 0, 50, 50);
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
    nameLabel.setText("Mod", juce::NotificationType::dontSendNotification);
    nameLabel.setFont(20.0f);  

    amountSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    amountSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    amountSlider.setPopupDisplayEnabled(true, true, this);
    //amountSlider.setTextValueSuffix (" Mod Amount");
    amountSlider.setRange(0.0f, 10.0f, 0.1f);
    amountSlider.setValue(5.0f);
    addAndMakeVisible(amountSlider);
    amountSlider.setBounds(0, 0, 100, 100);

    addAndMakeVisible(amountLabel);
    amountLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    amountLabel.setJustificationType(juce::Justification::topLeft);
    amountLabel.setText("Amount", juce::NotificationType::dontSendNotification);
    amountLabel.setFont(fontDim);
    
    delaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delaySlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    delaySlider.setPopupDisplayEnabled(true, true, this);
    //delaySlider.setTextValueSuffix (" Mod Amount");
    delaySlider.setRange(0.0f, 10.0f, 0.1f);
    delaySlider.setValue(5.0f);
    addAndMakeVisible(delaySlider);
    delaySlider.setBounds(0, 0, 100, 100);

    addAndMakeVisible(delayLabel);
    delayLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    delayLabel.setJustificationType(juce::Justification::topLeft);
    delayLabel.setText("Delay", juce::NotificationType::dontSendNotification);
    delayLabel.setFont(fontDim);

    rateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    rateSlider.setPopupDisplayEnabled(true, true, this);
    //rateSlider.setTextValueSuffix (" Mod Rate");
    rateSlider.setRange(0.0f, 10.0f, 0.1f);
    rateSlider.setValue(5.0f);
    addAndMakeVisible(rateSlider);
    rateSlider.setBounds(0, 0, 100, 100);

    addAndMakeVisible(rateLabel);
    rateLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    rateLabel.setJustificationType(juce::Justification::topLeft);
    rateLabel.setText("Rate", juce::NotificationType::dontSendNotification);
    rateLabel.setFont(fontDim);

}

ModulationComponent::~ModulationComponent()
{
}

void ModulationComponent::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds(), 3);   // draw an outline around the component

    /*
    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Reverb", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
    */
}

void ModulationComponent::resized()
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

        juce::GridItem(rateSlider).withSize(70.0f, 70.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 0, 0))
            .withArea(2, 2),

        juce::GridItem(rateLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::end)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 0, 30.0f))
            .withArea(5, 2),
        
        juce::GridItem(amountSlider).withSize(sliderDim, sliderDim)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(0.0f, 10.0f, 10.0f, 0))
            .withArea(6, 3),

        juce::GridItem(amountLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin(10.0f, 25.0f, 0, 1.0f))
            .withArea(7, 3),
        
        juce::GridItem(delaySlider).withSize(sliderDim, sliderDim)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin(0.0f, 0.0f, 10.0f, 10.0f))
            .withArea(6, 1),

        juce::GridItem(delayLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 0, 13.0f))
            .withArea(7, 1),
    };

    grid.performLayout(getLocalBounds());

}

