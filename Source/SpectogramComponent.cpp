/*
  ==============================================================================

    SpectogramComponent.cpp
    Created: 7 Nov 2020 2:10:03am
    Author:  Robin Otterbein

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SpectogramComponent.h"

//==============================================================================
SpectogramComponent::SpectogramComponent()
{
   
}

SpectogramComponent::~SpectogramComponent()
{
}

void SpectogramComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.drawRect (getLocalBounds(), 3);   // draw an outline around the component

    /*
    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Spectogram", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text*/
}

void SpectogramComponent::resized()
{
    juce::Grid grid;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    //5 rows
    grid.templateRows = {
        Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)),
        Track(Fr(1))
    };
    //10 columns
    grid.templateColumns = {
        Track(Fr(1)), Track(Fr(1))
    };

    grid.rowGap = juce::Grid::Px(10.0f);
    grid.columnGap = juce::Grid::Px(10.0f);

    float buttonDim = 65.0f;

    grid.items = {

    };

    grid.performLayout(getLocalBounds());
}
