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

class AdditiveComponent  : public juce::Component, public juce::Slider::Listener
{
public:
    AdditiveComponent();
    ~AdditiveComponent() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(juce::Slider* slider) override;
    
    struct AdditiveListener
    {
        virtual void onAddAmpChange(double addAmp) = 0;
        virtual void onShiftValueChange(double shiftValue) = 0;
        virtual void onStretchValueChange(double stretchValue) = 0;
    };

    void setAdditiveListener(AdditiveListener* addListener);

private:
    
    juce::ToggleButton onoffButton;
    juce::Label nameLabel;
    juce::Label onoffLabel;
    HarmonicEditor harmonicEditor;
    
    juce::Label shiftLabel;
    
    juce::Slider stretchSlider;
    juce::Label stretchLabel;
    juce::Slider ampSlider;
    
    
    double addAmp = 0;
    double shiftValue;
    double stretchValue;
    
    AdditiveListener* additiveListener = NULL;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdditiveComponent)
};
