/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"

//==============================================================================
DdspsynthAudioProcessorEditor::DdspsynthAudioProcessorEditor (DdspsynthAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState(vts), mainComponent(vts)
{
    //LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName("Avenir Next");

    backgroundTexture = backgroundTexture.rescaled(900, 600);
    addAndMakeVisible(mainComponent);
	additive = (AdditiveComponent*)mainComponent.findChildWithID("additive");
	harmEditor = (HarmonicEditor*)(additive->findChildWithID("harmonicEditor"));
    subtractive = (SubtractiveComponent*)(mainComponent.findChildWithID("subtractive"));
    output = (OutputComponent*)mainComponent.findChildWithID("output");


	harmEditor->setListener(&p);
 //   subtractive->setSubtractiveListener(this);
 //   additive->setAdditiveListener(this);
 //   output->setOutputListener(this);
	
    mainComponent.setBounds(20, 20, 860, 560);
    startTimerHz (60);
    setSize (900, 600);
    
    mainComponent.setLookAndFeel(&otherLookAndFeel);

    defaultTreeState = vts.copyState();
}

DdspsynthAudioProcessorEditor::~DdspsynthAudioProcessorEditor()
{
    mainComponent.setLookAndFeel(nullptr);
}

//==============================================================================
void DdspsynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    
    g.drawImageAt(backgroundTexture, 0, 0);
    
}

void DdspsynthAudioProcessorEditor::resized()
{
    
}

//===============================================================================
// Spectrogram methods
void DdspsynthAudioProcessorEditor::timerCallback()
{
    if (audioProcessor.getNextFFTBlockReady())
    {
        mainComponent.drawNextLineOfSpectrogram(audioProcessor.getFftSize(),
                                                audioProcessor.getFftData(),
                                                *audioProcessor.getForwardFFT(),
                                                audioProcessor.getFftOrder());
        audioProcessor.setNextFFTBlockReady(false);
    }
    setNumberOfHarmonics(audioProcessor.getNumberOfHarmonics());
}

void DdspsynthAudioProcessorEditor::setNumberOfHarmonics(int numberOfHarmonics)
{
    if (harmEditor != nullptr)
    {
        harmEditor->setNumberOfHarmonicSliders(numberOfHarmonics);
    }
}

void DdspsynthAudioProcessorEditor::resetParameters()
{
    harmEditor->resetSliders();
    //valueTreeState.replaceState(defaultTreeState);
    //defaultTreeState = valueTreeState.copyState();
}


//void DdspsynthAudioProcessorEditor::onNoiseColorChange(double color)
//{
//    audioProcessor.onNoiseColorChange(color);
//}
//
//void DdspsynthAudioProcessorEditor::onOnOffSubChange(bool onOff)
//{
//    audioProcessor.onOnOffSubChange(onOff);
//}
//
//void DdspsynthAudioProcessorEditor::onShiftValueChange(double shiftValue)
//{
//    audioProcessor.onShiftValueChange(shiftValue);
//}
//
//void DdspsynthAudioProcessorEditor::onStretchValueChange(double stretchValue)
//{
//    audioProcessor.onStretchValueChange(stretchValue);
//}
//
//void DdspsynthAudioProcessorEditor::onOnOffAddChange(bool onOff)
//{
//    audioProcessor.onOnOffAddChange(onOff);
//}
//
//void DdspsynthAudioProcessorEditor::onSubAmpChange(double subAmp)
//{
//    audioProcessor.onSubAmpChange(subAmp);
//}
//
//void DdspsynthAudioProcessorEditor::onAddAmpChange(double addAmp)
//{
//    audioProcessor.onAddAmpChange(addAmp);
//}
//
//void DdspsynthAudioProcessorEditor::onOutAmpChange(double outAmp)
//{
//    audioProcessor.onOutAmpChange(outAmp);
//}


