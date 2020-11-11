/*
  ==============================================================================

    HarmonicSlider.h
    Created: 10 Nov 2020 4:48:26pm
    Author:  Robin Otterbein

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class HarmonicSlider  : public juce::Component
{
public:
    HarmonicSlider();
    ~HarmonicSlider() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setValue(float);

private:
    bool isEntered;
    bool isDown;
    
    juce::Colour colour;
    juce::Rectangle<int> rectangle;
    float value;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HarmonicSlider)
};
