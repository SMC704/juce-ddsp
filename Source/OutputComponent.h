/*
  ==============================================================================

    OutputComponent.h
    Created: 7 Nov 2020 2:09:43am
    Author:  Robin Otterbein

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OutputComponent  : public juce::Component/*, public juce::Slider::Listener*/
{
public:
    OutputComponent(juce::AudioProcessorValueTreeState&);
    ~OutputComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    //void sliderValueChanged(juce::Slider* slider) override;
    //
    //struct OutputListener
    //{
    //    virtual void onOutAmpChange(double outAmp) = 0;
    //};

    //void setOutputListener(OutputListener* outListener);

private:

    juce::AudioProcessorValueTreeState& valueTreeState;

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    juce::Label nameLabel;
    juce::Slider masterSlider;
    juce::Label masterLabel;
    std::unique_ptr <SliderAttachment> masterAttachment;
    
    //OutputListener* outputListener = NULL;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputComponent)
};
