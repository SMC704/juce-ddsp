/*
  ==============================================================================

    AdditiveComponent.h
    Created: 7 Nov 2020 2:08:52am
    Author:  Robin Otterbein

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "HarmonicEditor.h"

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
    
    juce::ToggleButton onoffButton;
    juce::Label nameLabel;
    juce::Label onoffLabel;
    HarmonicEditor harmonicEditor;
    
    juce::Slider shiftSlider;
    juce::Label shiftLabel;
    juce::Slider stretchSlider;
    juce::Label stretchLabel;
    juce::Slider ampSlider;
    juce::Label ampLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdditiveComponent)
};
