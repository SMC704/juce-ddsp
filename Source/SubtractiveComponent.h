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
class SubtractiveComponent  : public juce::Component/*, public juce::Slider::Listener, public juce::ToggleButton::Listener*/
{
public:
    SubtractiveComponent(juce::AudioProcessorValueTreeState&);
    ~SubtractiveComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;


    //struct SubtractiveListener
    //{
    //    virtual void onNoiseColorChange(double color) = 0;
    //    virtual void onOnOffSubChange(bool onOff) = 0;
    //    virtual void onSubAmpChange(double subAmp) = 0;
    //};

    //void setSubtractiveListener(SubtractiveListener* subListener);

private:

    juce::AudioProcessorValueTreeState& valueTreeState;

    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    juce::ImageButton onoffButton;
    std::unique_ptr<ButtonAttachment> onoffAttachment;

    juce::Label nameLabel;
    juce::Label onoffLabel;
    juce::Slider ampSlider;
    juce::Label ampLabel;
    std::unique_ptr <SliderAttachment> ampAttachment;

    juce::Slider colourSlider;
    juce::Label colourLabel;
    std::unique_ptr <SliderAttachment> colorAttachment;

    double noiseColor = 0;
    double subAmp = 0;
    bool onOffState = true;

    //SubtractiveListener* subtractiveListener = NULL;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SubtractiveComponent)

        //// Inherited via Listener
        //void buttonClicked(juce::Button*) override;
        //void sliderValueChanged(juce::Slider* slider) override;

};
