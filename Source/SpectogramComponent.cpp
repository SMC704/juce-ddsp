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
    : spectrogramImage (juce::Image::RGB, 512, 512, true)
{
    
}

SpectogramComponent::~SpectogramComponent()
{
}

void SpectogramComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.drawRect (getLocalBounds(), 3);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Spectogram", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
    
    g.fillAll (juce::Colours::black);

    g.setOpacity (1.0f);
    g.drawImage (spectrogramImage, getLocalBounds().toFloat());
}

void SpectogramComponent::resized()
{
}

void SpectogramComponent::drawNextLineOfSpectrogram(int fftSize, float* fftData, juce::dsp::FFT& forwardFFT, int fftOrder)
{
    auto rightHandEdge = spectrogramImage.getWidth() - 1;
    auto imageHeight   = spectrogramImage.getHeight();
    
    float extractedFftData [2 * fftSize];
    
    for (int i = 0; i < (2 * fftSize - 1); ++i)
    {
        extractedFftData[i] = *fftData;
        fftData++;
    }
    
    // first, shuffle our image leftwards by 1 pixel..
    spectrogramImage.moveImageSection (0, 0, 1, 0, rightHandEdge, imageHeight);

    // then render our FFT data..
    forwardFFT.performFrequencyOnlyForwardTransform (extractedFftData);

    // find the range of values produced, so we can scale our rendering to
    // show up the detail clearly
    auto maxLevel = juce::FloatVectorOperations::findMinAndMax (extractedFftData, fftSize / 2);

    for (auto y = 1; y < imageHeight; ++y)
    {
        auto skewedProportionY = 1.0f - std::exp (std::log ((float) y / (float) imageHeight) * 0.2f);
        auto fftDataIndex = juce::jlimit (0, fftSize / 2, (int) (skewedProportionY * (int) fftSize / 2));
        auto level = juce::jmap (extractedFftData[fftDataIndex], 0.0f, juce::jmax (maxLevel.getEnd(), 1e-5f), 0.0f, 1.0f);

        spectrogramImage.setPixelAt (rightHandEdge, y, juce::Colour::fromHSL (-level*0.6+1, 1.0f, 0.5f, level));
    }
    
    repaint();
}
