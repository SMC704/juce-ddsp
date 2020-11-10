/*
  ==============================================================================

    AdditiveComponent.h
    Created: 7 Nov 2020 2:08:52am
    Author:  Robin Otterbein

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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
    
    juce::Slider shiftSlider;
    juce::Slider stretchSlider;
    juce::Slider ampSlider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdditiveComponent)
};
