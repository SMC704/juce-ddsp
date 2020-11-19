/*
  ==============================================================================

    AdditiveComponent.cpp
    Created: 7 Nov 2020 2:08:52am
    Author:  Robin Otterbein

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdditiveComponent.h"

using namespace juce;

//==============================================================================
AdditiveComponent::AdditiveComponent()
{
    shiftSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    shiftSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    shiftSlider.setPopupDisplayEnabled(true, true, this);
    shiftSlider.setTextValueSuffix (" Hz or whatever");
    shiftSlider.setRange(0.0f, 10.0f, 0.1f);
    shiftSlider.setValue(5.0f);
    addAndMakeVisible(shiftSlider);
    shiftSlider.setBounds(0, 0, 100, 100);

    
    stretchSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    stretchSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    stretchSlider.setPopupDisplayEnabled(true, true, this);
    stretchSlider.setTextValueSuffix (" Hz or whatever");
    stretchSlider.setRange(0.0f, 10.0f, 0.1f);
    stretchSlider.setValue(5.0f);
    addAndMakeVisible(stretchSlider);
    stretchSlider.setBounds(0, 0, 100, 100);
    
    
    ampSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ampSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    ampSlider.setPopupDisplayEnabled(true, true, this);
    ampSlider.setTextValueSuffix (" Hz or whatever");
    ampSlider.setRange(0.0f, 10.0f, 0.1f);
    ampSlider.setValue(5.0f);
    addAndMakeVisible(ampSlider);
    ampSlider.setBounds(0, 0, 100, 100);
    
    
    addAndMakeVisible(shiftSliderLabel);
    shiftSliderLabel.setText("Shift", juce::dontSendNotification);
    shiftSliderLabel.setJustificationType(Justification::centred);
    
    addAndMakeVisible(stretchSliderLabel);
    stretchSliderLabel.setText("Stretch", juce::dontSendNotification);
    stretchSliderLabel.setJustificationType(Justification::centred);

    
    addAndMakeVisible(ampSliderLabel);
    ampSliderLabel.setText("Amp", juce::dontSendNotification);
    ampSliderLabel.setJustificationType(Justification::centred);
    
    addAndMakeVisible(moduleToggle);
        
}

AdditiveComponent::~AdditiveComponent()
{
}

void AdditiveComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.drawRect (getLocalBounds(), 3);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Additive", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text

    
}

void AdditiveComponent::resized()
{
    juce::Grid grid;
     
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows    = {
        Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1)),
        Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1))
    };
    grid.templateColumns = {
        Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1)),
        Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1)),
        Track (Fr (1)), Track (Fr (1)), Track (Fr (1)), Track (Fr (1))
    };
    
    grid.rowGap = juce::Grid::Px(10.0f);
    grid.columnGap = juce::Grid::Px(10.0f);

    grid.items = {
        juce::GridItem (shiftSlider).withArea(6, 2, 9, 4),
        juce::GridItem (stretchSlider).withArea(6, 4, 9, 6),
        juce::GridItem (ampSlider).withArea(6, 10, 9, 12),
        juce::GridItem (shiftSliderLabel).withArea(8, 2, 11, 4),
        juce::GridItem (stretchSliderLabel).withArea(8, 4, 11, 6),
        juce::GridItem (ampSliderLabel).withArea(8, 10, 11, 12),
        juce::GridItem (moduleToggle).withArea(1, 12, 1, 12)
    };

    grid.performLayout (getLocalBounds());
    
}
