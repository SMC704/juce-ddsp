/*
  ==============================================================================

    SubtractiveComponent.h
    Created: 7 Nov 2020 2:09:03am
    Author:  Robin Otterbein

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SubtractiveComponent  : public juce::Component, public juce::Slider::Listener 
{
public:
    SubtractiveComponent();
    ~SubtractiveComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

        struct SubtractiveListener
        {
            virtual void onNoiseColorChange(double color) = 0;
            virtual void onSubAmpChange(double subAmp) = 0;
            
        };

        void setSubtractiveListener(SubtractiveListener* subListener);

    private:
        

        juce::ToggleButton onoffButton;
        juce::Label nameLabel;
        juce::Label onoffLabel;
        juce::Slider ampSlider;
        juce::Label ampLabel;
        juce::Label lfoLabel;
        juce::Slider amoutSlider;
        juce::Label amountLabel;
        juce::Slider rateSlider;
        juce::Label rateLabel;
        juce::Slider colourSlider;
        juce::Label colourLabel;

        double noiseColor = 0;
        double subAmp = 0;

        SubtractiveListener* subtractiveListener = NULL;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SubtractiveComponent)
    };
