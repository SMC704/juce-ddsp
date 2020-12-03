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
    onoffButton.addListener(this);
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
    nameLabel.setText("Additive", juce::NotificationType::dontSendNotification);
    nameLabel.setFont(20.0f);

	addChildAndSetID(&harmonicEditor, "harmonicEditor");
    harmonicEditor.setBounds(0, 0, 100, 100);
    
    shiftSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    shiftSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    shiftSlider.setPopupDisplayEnabled(true, true, this);
    //shiftSlider.setTextValueSuffix (" Halftones");
    shiftSlider.setRange(-12.0f, 12.0f, 0.01f);
    shiftSlider.setValue(0);
    addAndMakeVisible(shiftSlider);
    shiftSlider.setBounds(0, 0, 100, 100);
    shiftSlider.addListener(this);
    shiftSlider.setDoubleClickReturnValue(true, 0.0f);


    addAndMakeVisible(shiftLabel);
    shiftLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    shiftLabel.setJustificationType(juce::Justification::topLeft);
    shiftLabel.setText("Shift", juce::NotificationType::dontSendNotification);
    shiftLabel.setFont(fontDim);

    stretchSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    stretchSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    stretchSlider.setPopupDisplayEnabled(true, true, this);
    //stretchSlider.setTextValueSuffix (" ");
    stretchSlider.setRange(-1.0f, 1.0f, 0.01f);
    stretchSlider.setValue(0.0f);
    addAndMakeVisible(stretchSlider);
    stretchSlider.setBounds(0, 0, 100, 100);
    stretchSlider.addListener(this);
    stretchSlider.setDoubleClickReturnValue(true, 0.0f);

    addAndMakeVisible(stretchLabel);
    stretchLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    stretchLabel.setJustificationType(juce::Justification::topLeft);
    stretchLabel.setText("Stretch", juce::NotificationType::dontSendNotification);
    stretchLabel.setFont(fontDim);
 
    ampSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ampSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    ampSlider.setPopupDisplayEnabled(true, true, this);
    ampSlider.setTextValueSuffix (" dB");
    ampSlider.setRange(-60.0f, 0.0f, 0.1f);
    ampSlider.setValue(-6.0f);
    addAndMakeVisible(ampSlider);
    ampSlider.setBounds(0, 0, 100, 100);
    ampSlider.addListener(this);
    ampSlider.setDoubleClickReturnValue(true, -6.0f);

    addAndMakeVisible(ampLabel);
    ampLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    ampLabel.setJustificationType(juce::Justification::topLeft);
    ampLabel.setText("Amp", juce::NotificationType::dontSendNotification);
    ampLabel.setFont(fontDim);
    
    shiftValue = 0;
    stretchValue = 0;
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
            .withMargin(juce::GridItem::Margin(10.0f))
            .withArea(1, 3),

        juce::GridItem(shiftSlider).withSize(sliderDim, sliderDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 0, 0))
            .withArea(4, 1),

        juce::GridItem(shiftLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::end)
            .withJustifySelf(juce::GridItem::JustifySelf::center)
            .withMargin(juce::GridItem::Margin(0, 0, 0, 27.0f))
            .withArea(5, 1),

        juce::GridItem(stretchSlider).withSize(sliderDim, sliderDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 0, 0))
            .withArea(4, 1),

        juce::GridItem(stretchLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::end)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(0, -14.0f, 0, 0))
            .withArea(5, 1),

        juce::GridItem(ampSlider).withSize(sliderDim, sliderDim)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(10.0f, 0, 0, 0))
            .withArea(4, 2),

        juce::GridItem(ampLabel).withSize(65.0f, 30.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::end)
            .withJustifySelf(juce::GridItem::JustifySelf::end)
            .withMargin(juce::GridItem::Margin(0, -21.0f, 0, 0))
            .withArea(5, 2),

        juce::GridItem(harmonicEditor).withSize(360.0f, 130.0f)
            .withAlignSelf(juce::GridItem::AlignSelf::start)
            .withJustifySelf(juce::GridItem::JustifySelf::start)
            .withMargin(juce::GridItem::Margin(50.0f, 30.0f, 30.0f, 30.0f))
            .withArea(1, 1),
    };

    grid.performLayout (getLocalBounds());
    
}

void AdditiveComponent::sliderValueChanged(juce::Slider* slider)
{
   if (additiveListener != NULL) {
        if (slider == &ampSlider) {
            addAmp = ampSlider.getValue();
            additiveListener->onAddAmpChange(addAmp);
        }
        else if (slider == &shiftSlider)
        {
            shiftValue = slider->getValue();
            additiveListener->onShiftValueChange(shiftValue);
        }
        else if (slider == &stretchSlider)
        {
            stretchValue = slider->getValue();
            additiveListener->onStretchValueChange(stretchValue);
        }
    }
}

void AdditiveComponent::setAdditiveListener(AdditiveListener* addListener)
{
    additiveListener = addListener;
    if (additiveListener != NULL)
        additiveListener->onAddAmpChange(0);
        additiveListener->onShiftValueChange(shiftValue);
        additiveListener->onStretchValueChange(stretchValue);
        additiveListener->onOnOffAddChange(onOffState);
}

void AdditiveComponent::buttonClicked(juce::Button* button)
{
    additiveListener->onOnOffAddChange(button->getToggleState());
}
