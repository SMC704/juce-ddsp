/*
  ==============================================================================

    AdditiveComponent.cpp
    Created: 7 Nov 2020 2:08:52am
    Author:  Robin Otterbein

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdditiveComponent.h"

//==============================================================================
AdditiveComponent::AdditiveComponent()
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
    nameLabel.setText("Additive", juce::NotificationType::dontSendNotification);
    nameLabel.setFont(20.0f);

    shiftSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    shiftSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    shiftSlider.setPopupDisplayEnabled(true, true, this);
    shiftSlider.setTextValueSuffix (" Hz or whatever");
    shiftSlider.setRange(0.0f, 10.0f, 0.1f);
    shiftSlider.setValue(5.0f);
    addAndMakeVisible(shiftSlider);
    shiftSlider.setBounds(0, 0, 100, 100);

    addAndMakeVisible(shiftLabel);
    shiftLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    shiftLabel.setJustificationType(juce::Justification::topLeft);
    shiftLabel.setText("Shift", juce::NotificationType::dontSendNotification);
    shiftLabel.setFont(fontDim);

    stretchSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    stretchSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    stretchSlider.setPopupDisplayEnabled(true, true, this);
    stretchSlider.setTextValueSuffix (" Hz or whatever");
    stretchSlider.setRange(0.0f, 10.0f, 0.1f);
    stretchSlider.setValue(5.0f);
    addAndMakeVisible(stretchSlider);
    stretchSlider.setBounds(0, 0, 100, 100);

    addAndMakeVisible(stretchLabel);
    stretchLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    stretchLabel.setJustificationType(juce::Justification::topLeft);
    stretchLabel.setText("Stretch", juce::NotificationType::dontSendNotification);
    stretchLabel.setFont(fontDim);
 
    ampSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ampSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    ampSlider.setPopupDisplayEnabled(true, true, this);
    ampSlider.setTextValueSuffix (" Hz or whatever");
    ampSlider.setRange(0.0f, 10.0f, 0.1f);
    ampSlider.setValue(5.0f);
    addAndMakeVisible(ampSlider);
    ampSlider.setBounds(0, 0, 100, 100);

    addAndMakeVisible(ampLabel);
    ampLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    ampLabel.setJustificationType(juce::Justification::topLeft);
    ampLabel.setText("Amp", juce::NotificationType::dontSendNotification);
    ampLabel.setFont(fontDim);
}

AdditiveComponent::~AdditiveComponent()
{
}

void AdditiveComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.drawRect (getLocalBounds(), 3);   // draw an outline around the component

    /*
    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Additive", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text*/
}

void AdditiveComponent::resized()
{
    juce::Grid grid;
     
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    //4 rows
    grid.templateRows    = {
        Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1))
    };
    //2 columns
    grid.templateColumns = {
        Track (Fr (1)), Track (Fr (1)), 
    };
    
    grid.rowGap = juce::Grid::Px(10.0f);
    grid.columnGap = juce::Grid::Px(10.0f);

    float sliderDim = 60.0f;

    grid.items = {

        juce::GridItem(nameLabel).withSize(100.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin::Margin(10.0f))
            .withArea(1, 1),

        juce::GridItem(onoffButton).withSize(40.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin::Margin(10.0f))
            .withArea(1, 3),

        juce::GridItem(shiftSlider).withSize(sliderDim, sliderDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin::Margin(10.0f, 0, 0, 0))
            .withArea(4, 1),

        juce::GridItem(shiftLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::end)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin::Margin(0, 0, 0, 24.0f))
            .withArea(5, 1),

        juce::GridItem(stretchSlider).withSize(sliderDim, sliderDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin::Margin(10.0f, 0, 0, 0))
            .withArea(4, 1),

        juce::GridItem(stretchLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::end)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin::Margin(0, -8.0f, 0, 0))
            .withArea(5, 1),

        juce::GridItem(ampSlider).withSize(sliderDim, sliderDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin::Margin(10.0f, 0, 0, 0))
            .withArea(4, 2),

        juce::GridItem(ampLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::end)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin::Margin(0, -15.0f, 0, 0))
            .withArea(5, 2),

        //juce::GridItem (ampSlider).withArea(6, 10, 9, 12)
    };

    grid.performLayout (getLocalBounds());
    
}
