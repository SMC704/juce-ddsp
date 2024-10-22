/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "InputComponent.h"
#include "ModelComponent.h"
#include "AdditiveComponent.h"
#include "SubtractiveComponent.h"
#include "ModulationComponent.h"
#include "ReverbComponent.h"
#include "SpectogramComponent.h"
#include "OutputComponent.h"
#include "MainComponent.h"
#include "CustomLookAndFeel.h"

//==============================================================================
/**
*/
class DdspsynthAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer/*, public SubtractiveComponent::SubtractiveListener, public AdditiveComponent::AdditiveListener, public OutputComponent::OutputListener*/
{
public:
    DdspsynthAudioProcessorEditor (DdspsynthAudioProcessor&, juce::AudioProcessorValueTreeState&, juce::AudioProcessorValueTreeState&);
    ~DdspsynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    //==============================================================================
    void timerCallback() override;

    void setNumberOfHarmonics(int numberOfHarmonics);
    void resetParameters();

private:
    AdditiveComponent* additive;
    HarmonicEditor* harmEditor;
    SubtractiveComponent* subtractive;
    OutputComponent* output;

    DdspsynthAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& synthVTS;
    juce::AudioProcessorValueTreeState& modelVTS;

    juce::Image backgroundTexture = juce::ImageFileFormat::
        loadFrom(BinaryData::background_texture_dark_headline_png, 
            BinaryData::background_texture_dark_headline_pngSize);
    
    MainComponent mainComponent;
    
    OtherLookAndFeel otherLookAndFeel;
    
    juce::ValueTree defaultTreeState;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DdspsynthAudioProcessorEditor)

        //// Inherited via SubtractiveListener
        //virtual void onNoiseColorChange(double color) override;
        //virtual void onOnOffSubChange(bool onOff) override;
        //virtual void onSubAmpChange(double subAmp) override;
    
        //// Inherited via AdditiveListener
        //virtual void onAddAmpChange(double addAmp) override;
        //virtual void onShiftValueChange(double shiftValue) override;
        //virtual void onStretchValueChange(double stretchValue) override;
        //virtual void onOnOffAddChange(bool onOff) override;
    
        //// Inherited via OutputListener
        //virtual void onOutAmpChange(double outAmp) override;
};
