/*
  ==============================================================================

    DDSPSound.h
    Created: 17 Nov 2020 3:04:22pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include "HarmonicEditor.h"

struct DDSPSound : public juce::SynthesiserSound
{
	DDSPSound() {
		for (int i = 0; i < 50; i++) {
			harmonics[i] = 0.5;
		}
	};
	~DDSPSound() {};

	double harmonics[50];

	bool appliesToNote(int) override { return true; }
	bool appliesToChannel(int) override { return true; }
};