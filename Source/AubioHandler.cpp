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
    const char* libFileName;
#if JUCE_WINDOWS
    libFileName = "libaubio-5.dll";
#elif JUCE_MAC
    // TODO mac
#endif
    bool loaded = abLibrary.open(cwd.getFullPathName() + juce::File::getSeparatorString() + libFileName);

    fpNewAubioPitch = (fptypeNewAubioPitch)abLibrary.getFunction("new_aubio_pitch");
    fpDelAubioPitch = (fptypeDelAubioPitch)abLibrary.getFunction("del_aubio_pitch");
    fpAubioPitchDo = (fptypeAubioPitchDo)abLibrary.getFunction("aubio_pitch_do");
}

AubioHandler::~AubioHandler()
{
    abLibrary.close();
}

void AubioHandler::prepare(const char_t* method, uint_t bufsize, uint_t hopsize, uint_t sampleRate)
{
    aubioPitch.reset(fpNewAubioPitch(method, bufsize, hopsize, sampleRate));
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

    fpAubioPitchDo(aubioPitch.get(), &aubioInput, &aubioOutput);
    return result;
}

void AubioHandler::PitchDeleter::operator()(aubio_pitch_t * p)
{
    AubioHandler::getInstance().fpDelAubioPitch(p);
}
