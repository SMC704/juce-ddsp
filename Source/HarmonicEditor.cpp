/*
  ==============================================================================

    HarmonicEditor.cpp
    Created: 10 Nov 2020 2:44:17pm
    Author:  Robin Otterbein

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HarmonicEditor.h"

//==============================================================================
HarmonicEditor::HarmonicEditor()
{
    isEntered = false;
    isDown = false;
    createHarmonicSliders();

}

HarmonicEditor::~HarmonicEditor()
{
}

void HarmonicEditor::paint (juce::Graphics& g)
{

}

void HarmonicEditor::setListener(HarmonicEditor::Listener* pTheListener)
{
	pListener = pTheListener;
	if (pListener != NULL) {
		pListener->onHarmonicsChange(harmonicValues, nHarmonics);
	}
}

void HarmonicEditor::setNumberOfHarmonicSliders(int nHarmonicsNew)
{
    if (nHarmonics != nHarmonicsNew)
    {
        nHarmonics = nHarmonicsNew;
        createHarmonicSliders();
    }
}

void HarmonicEditor::createHarmonicSliders()
{
    harmonicSliders.clear();

    for (int i = 0; i < nHarmonics; i++) {
        harmonicSliders.add(new HarmonicSlider());
        harmonicValues[i] = 0.5;
    }

    for (HarmonicSlider* harmonicSlider : harmonicSliders) {
        addAndMakeVisible(harmonicSlider);
        harmonicSlider->setBounds(0, 0, 100, 100);
        harmonicSlider->addMouseListener(this, true);
    }
    resized();
}

void HarmonicEditor::resetSliders()
{
    for (int i = 0; i < nHarmonics; i++)
    {
        harmonicSliders[i]->setValue(0.5);
        harmonicValues[i] = 0.5;
    }

    repaint();
    if (pListener != NULL) {
        pListener->onHarmonicsChange(harmonicValues, nHarmonics);
    }
}

void HarmonicEditor::resized()
{
    juce::Grid grid;
     
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows    = { Track (Fr (1))
    };
    
    for (int i=0; i < nHarmonics; i++) {
        grid.templateColumns.add(Track (Fr (1)));
        grid.items.add(juce::GridItem (harmonicSliders[i]));
    }

    grid.performLayout (getLocalBounds());
}

void HarmonicEditor::mouseEnter(const juce::MouseEvent &event)
{
    isEntered = true;
}

void HarmonicEditor::mouseExit(const juce::MouseEvent &event)
{
    isEntered = false;
}

void HarmonicEditor::mouseDown(const juce::MouseEvent &event)
{
    isDown = true;
}

void HarmonicEditor::mouseUp(const juce::MouseEvent &event)
{
    isDown = false;
}

void HarmonicEditor::mouseDrag(const juce::MouseEvent &event)
{
    if (isEntered && isDown) {
        int mousePositionX = event.getScreenX();
        int mousePositionY = event.getScreenY();
        int editorPositionX = getScreenX();
        int editorPositionY = getScreenY();
        int relativePositionX = mousePositionX - editorPositionX;
        int relativePositionY = mousePositionY - editorPositionY;
        int editorWidth = getWidth();
        int editorHeight = getHeight();
        int nActiveSlider =  relativePositionX / (editorWidth/nHarmonics);
        float newValue = float(relativePositionY) / float(editorHeight);
        if(nActiveSlider >= 0 && nActiveSlider < nHarmonics) {
            harmonicSliders[nActiveSlider]->setValue(newValue);
			harmonicValues[nActiveSlider] = newValue;
        }

		if (pListener != NULL) {
			pListener->onHarmonicsChange(harmonicValues, nHarmonics);
		}
        repaint();
    }
}