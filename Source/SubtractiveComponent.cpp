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

    addAndMakeVisible(onoffLabel);
    onoffLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    onoffLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(nameLabel);
    nameLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    nameLabel.setJustificationType(juce::Justification::topLeft);
    nameLabel.setText("Subtractive", juce::NotificationType::dontSendNotification);
    nameLabel.setFont(20.0f);

    ampSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ampSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    ampSlider.setRange(0.0f, 10.0f, 0.1f);
    ampSlider.setValue(5.0f);
    addAndMakeVisible(ampSlider);
    ampSlider.setBounds(0, 0, 100, 100);

    addAndMakeVisible(ampLabel);
    ampLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    ampLabel.setJustificationType(juce::Justification::topLeft);
    ampLabel.setText("Amp", juce::NotificationType::dontSendNotification);
    ampLabel.setFont(fontDim);

    addAndMakeVisible(lfoLabel);
    lfoLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    lfoLabel.setJustificationType(juce::Justification::topLeft);
    lfoLabel.setText("L\nF\nO", juce::NotificationType::dontSendNotification);
    lfoLabel.setFont(20.0f);

    amoutSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    amoutSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
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
    rateSlider.setRange(0.0f, 10.0f, 0.1f);
    rateSlider.setValue(5.0f);
    addAndMakeVisible(rateSlider);
    rateSlider.setBounds(0, 0, 100, 100);

    addAndMakeVisible(rateLabel);
    rateLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    rateLabel.setJustificationType(juce::Justification::topLeft);
    rateLabel.setText("Rate", juce::NotificationType::dontSendNotification);
    rateLabel.setFont(fontDim);

    colourSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    colourSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    colourSlider.setRange(-1.0f, 1.0f, 0.01f);
    colourSlider.setValue(0.0f);
    addAndMakeVisible(colourSlider);
    colourSlider.setBounds(0, 0, 100, 100);
    colourSlider.addListener(this);

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
    //2 columns
    grid.templateColumns = {
        Track(Fr(1)), Track(Fr(1))
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
            .withMargin(juce::GridItem::Margin(10.0f))
            .withArea(1, 2),

        juce::GridItem(colourSlider).withSize(70.0f, 70.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(0.0f))
            .withArea(4, 1),

        juce::GridItem(colourLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(20.0f, -5.0f, 0, 0))
            .withArea(5, 1),

        juce::GridItem(ampSlider).withSize(sliderDim, sliderDim)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 0, 20.0f))
            .withArea(7, 1),

        juce::GridItem(ampLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin(15.0f, 0, 0, 25.0f))
            .withArea(8, 1),

        juce::GridItem(lfoLabel).withSize(30.0f, 100.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin(20.0f, 35.0f, 0, 0))
            .withArea(6, 2),

        juce::GridItem(rateSlider).withSize(sliderDim, sliderDim)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(0.0f, 20.0f, 0, 0))
            .withArea(4, 2),

        juce::GridItem(rateLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(10.0f, 0.0f, 0, 0))
            .withArea(5, 2),

        juce::GridItem(amoutSlider).withSize(sliderDim, sliderDim)
            .withAlignSelf(juce::GridItem::AlignSelf::center)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(10.0f, 20.0f, 0, 0))
            .withArea(7, 2),

        juce::GridItem(amountLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(15.0f, 10.0f, 0, 0))
            .withArea(8, 2),
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
}

void SubtractiveComponent::setSubtractiveListener(SubtractiveListener* subListener)
{
    subtractiveListener = subListener;
    if (subtractiveListener != NULL)
        subtractiveListener->onNoiseColorChange(0);
}

void SubtractiveComponent::buttonClicked(juce::Button* button)
{
    subtractiveListener->onOnOffChange(button->getToggleState());
}