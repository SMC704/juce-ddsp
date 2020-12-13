/*
  ==============================================================================

    AubioHandler.h
    Created: 13 Dec 2020 6:52:04pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "aubio.h"
#include <memory>

class AubioHandler
{
public:

    // static singleton because the deleter needs access to the library...
    static AubioHandler& getInstance()
    {
        static AubioHandler instance;
        return instance;
    }

    void prepare(const char_t* method, uint_t bufsize, uint_t hopsize, uint_t sampleRate);
    void releaseResources();
    float process(juce::AudioBuffer<float> buffer);

private:
    AubioHandler();
    ~AubioHandler();

    juce::DynamicLibrary abLibrary;

	struct PitchDeleter
	{
        void operator()(aubio_pitch_t *p);
	};

    typedef aubio_pitch_t* (*fptypeNewAubioPitch) (const char_t*, uint_t, uint_t, uint_t);
    fptypeNewAubioPitch fpNewAubioPitch;

    typedef void (*fptypeDelAubioPitch) (aubio_pitch_t*);
    fptypeDelAubioPitch fpDelAubioPitch;

    typedef void (*fptypeAubioPitchDo) (aubio_pitch_t*, const fvec_t*, fvec_t*);
    fptypeAubioPitchDo fpAubioPitchDo;

	std::unique_ptr<aubio_pitch_t, PitchDeleter> aubioPitch;
};