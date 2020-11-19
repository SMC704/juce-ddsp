/*
  ==============================================================================

    OutputComponent.cpp
    Created: 7 Nov 2020 2:09:43am
    Author:  Robin Otterbein

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OutputComponent.h"

//==============================================================================
OutputComponent::OutputComponent()
{
    float fontDim = 15.0f;

    addAndMakeVisible(nameLabel);
    nameLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    nameLabel.setJustificationType(juce::Justification::topLeft);
    nameLabel.setText("Output", juce::NotificationType::dontSendNotification);
    nameLabel.setFont(20.0f);

    masterSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    masterSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    masterSlider.setRange(0.0f, 10.0f, 0.1f);
    masterSlider.setValue(5.0f);
    addAndMakeVisible(masterSlider);
    masterSlider.setBounds(0, 0, 100, 100);

    addAndMakeVisible(masterLabel);
    masterLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    masterLabel.setJustificationType(juce::Justification::topLeft);
    masterLabel.setText("Robin", juce::NotificationType::dontSendNotification);
    masterLabel.setFont(fontDim);
}

OutputComponent::~OutputComponent()
{
}

void OutputComponent::paint (juce::Graphics& g)
{

    g.setColour (juce::Colours::white);
    g.drawRect (getLocalBounds(), 3);   // draw an outline around the component

    /*
    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Output", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text*/
}

void OutputComponent::resized()
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

    float sliderDim = 60.0f;

    grid.items = {

         juce::GridItem(nameLabel).withSize(100.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin::Margin(10.0f))
            .withArea(1, 1),

        juce::GridItem(masterSlider).withSize(sliderDim, sliderDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin::Margin(0, 0, 0, 0))
            .withArea(1, 2),

        juce::GridItem(masterLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::end)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin::Margin(0, -15.0f, -5.0f, 0))
            .withArea(2, 2),

    };

    grid.performLayout(getLocalBounds());
}
