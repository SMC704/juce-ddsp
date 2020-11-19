/*
  ==============================================================================

    AdditiveComponent.h
    Created: 7 Nov 2020 2:08:52am
    Author:  Robin Otterbein

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

//==============================================================================
/*
*/

class AdditiveComponent  : public juce::Component
{
public:
    AdditiveComponent();
    ~AdditiveComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    Slider shiftSlider;
    Slider stretchSlider;
    Slider ampSlider;
    Label shiftSliderLabel;
    Label stretchSliderLabel;
    Label ampSliderLabel;
    ToggleButton moduleToggle;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdditiveComponent)
};
