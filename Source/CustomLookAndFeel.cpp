/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 18 Nov 2020 11:52:50am
    Author:  Erik Frej Knudsen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CustomLookAndFeel::CustomLookAndFeel()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    //mainComponent.setLookAndFeel(&otherLookAndFeel);

}

CustomLookAndFeel::~CustomLookAndFeel()
{
}

void CustomLookAndFeel::paint (juce::Graphics& g)
{


}

void CustomLookAndFeel::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}



