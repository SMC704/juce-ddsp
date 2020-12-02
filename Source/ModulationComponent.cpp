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

    addAndMakeVisible(onoffLabel);
    onoffLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    onoffLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(nameLabel);
    nameLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    nameLabel.setJustificationType(juce::Justification::topLeft);
    nameLabel.setText("Mod", juce::NotificationType::dontSendNotification);
    nameLabel.setFont(20.0f);  

    amoutSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    amoutSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    amoutSlider.setPopupDisplayEnabled(true, true, this);
    amoutSlider.setTextValueSuffix (" Mod Amount");
    amoutSlider.setRange(0.0f, 10.0f, 0.1f);
    amoutSlider.setValue(5.0f);
    addAndMakeVisible(amoutSlider);
    amoutSlider.setBounds(0, 0, 100, 100);

    addAndMakeVisible(amountLabel);
    amountLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    amountLabel.setJustificationType(juce::Justification::topLeft);
    amountLabel.setText("Amount", juce::NotificationType::dontSendNotification);
    amountLabel.setFont(fontDim);

    rateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    rateSlider.setPopupDisplayEnabled(true, true, this);
    rateSlider.setTextValueSuffix (" Mod Rate");
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

        juce::GridItem(onoffButton).withSize(40.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 10.0f, 0))
            .withArea(1, 3),

        juce::GridItem(rateSlider).withSize(70.0f, 70.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 0, 0))
            .withArea(2, 2),

        juce::GridItem(rateLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::end)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 0, 25.0f))
            .withArea(5, 2),
        
        juce::GridItem(amoutSlider).withSize(sliderDim, sliderDim)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(0.0f, -5.0f, 10.0f, 0))
            .withArea(6, 2),

        juce::GridItem(amountLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 0, 0))
            .withArea(7, 2),
    };

    grid.performLayout(getLocalBounds());

}

