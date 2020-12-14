/*
  ==============================================================================

    AubioHandler.cpp
    Created: 13 Dec 2020 6:52:04pm
    Author:  david

  ==============================================================================
*/

#include "AubioHandler.h"

AubioHandler::AubioHandler()
{
    juce::File cwd = juce::File::getSpecialLocation(juce::File::currentApplicationFile).getParentDirectory();
#if JUCE_WINDOWS
    const char* libFileName = "libaubio-5.dll";

    bool loaded = abLibrary.open(cwd.getFullPathName() + juce::File::getSeparatorString() + libFileName);

    fpNewAubioPitch = (fptypeNewAubioPitch)abLibrary.getFunction("new_aubio_pitch");
    fpDelAubioPitch = (fptypeDelAubioPitch)abLibrary.getFunction("del_aubio_pitch");
    fpAubioPitchDo = (fptypeAubioPitchDo)abLibrary.getFunction("aubio_pitch_do");
#endif
}

AubioHandler::~AubioHandler()
{
    abLibrary.close();
}

void AubioHandler::prepare(const char_t* method, uint_t bufsize, uint_t hopsize, uint_t sampleRate)
{
#if JUCE_WINDOWS
    aubioPitch.reset(fpNewAubioPitch(method, bufsize, hopsize, sampleRate));
#elif JUCE_MAC
    aubioPitch.reset(new_aubio_pitch(method, bufsize, hopsize, sampleRate));
#endif
}

void AubioHandler::releaseResources()
{
    aubioPitch.release();
}

float AubioHandler::process(juce::AudioBuffer<float> buffer)
{
    fvec_t aubioInput;
    fvec_t aubioOutput;
    float result;

    // need write pointer because the data type is not const
    aubioInput.data = buffer.getWritePointer(0);
    aubioInput.length = buffer.getNumSamples();

    aubioOutput.data = &result;
    aubioOutput.length = 1;
    
#if JUCE_WINDOWS
    fpAubioPitchDo(aubioPitch.get(), &aubioInput, &aubioOutput);
#elif JUCE_MAC
    aubio_pitch_do(aubioPitch.get(), &aubioInput, &aubioOutput);
#endif
    return result;
}

void AubioHandler::PitchDeleter::operator()(aubio_pitch_t * p)
{
#if JUCE_WINDOWS
    AubioHandler::getInstance().fpDelAubioPitch(p);
#elif JUCE_MAC
    del_aubio_pitch(p);
#endif
}
