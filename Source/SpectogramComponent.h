/*
  ==============================================================================

    SpectogramComponent.h
    Created: 7 Nov 2020 2:10:03am
    Author:  Robin Otterbein

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SpectogramComponent  : public juce::Component
{
public:
    SpectogramComponent();
    ~SpectogramComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectogramComponent)
};
