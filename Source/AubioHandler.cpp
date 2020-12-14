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
    fpSetTolerance = (fptypeSetTolerance)abLibrary.getFunction("aubio_pitch_set_tolerance");
    fpSetSilence = (fptypeSetSilence)abLibrary.getFunction("aubio_pitch_set_silence");
    fpGetConfidence = (fptypeGetConfidence)abLibrary.getFunction("aubio_pitch_get_confidence");
    fpGetLoudness = (fptypeGetLoudness)abLibrary.getFunction("aubio_db_spl");
#endif
}

AubioHandler::~AubioHandler()
{
    releaseResources();
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

AubioHandler::AubioResults AubioHandler::process(juce::AudioBuffer<float>& buffer)
{
    fvec_t aubioInput;
    fvec_t aubioOutput;
    AubioResults result;

    // need write pointer because the data type is not const
    aubioInput.data = buffer.getWritePointer(0);
    aubioInput.length = buffer.getNumSamples();

    aubioOutput.data = &result.pitch;
    aubioOutput.length = 1;
#if JUCE_WINDOWS

    fpAubioPitchDo(aubioPitch.get(), &aubioInput, &aubioOutput);
    result.confidence = fpGetConfidence(aubioPitch.get());
    result.loudness = fpGetLoudness(&aubioInput);
#elif JUCE_MAC
    aubio_pitch_do(aubioPitch.get(), &aubioInput, &aubioOutput);
    result.confidence = aubio_pitch_get_confidence(aubioPitch.get());
    result.loudness = aubio_db_spl(&aubioInput);
#endif
    return result;
}

uint_t AubioHandler::setTolerance(smpl_t tol)
{
#if JUCE_WINDOWS
    return fpSetTolerance(aubioPitch.get(), tol);
#elif JUCE_MAC
    return aubio_pitch_set_tolerance(aubioPitch.get(), tol);
#endif
}

uint_t AubioHandler::setSilence(smpl_t sil)
{
#if JUCE_WINDOWS
    return fpSetSilence(aubioPitch.get(), sil);
#elif JUCE_MAC
    return aubio_pitch_set_silence(aubioPitch.get(), sil);
#endif
}

void AubioHandler::PitchDeleter::operator()(aubio_pitch_t * p)
{
#if JUCE_WINDOWS
    AubioHandler::getInstance().fpDelAubioPitch(p);
#elif JUCE_MAC
    del_aubio_pitch(p);
#endif
}
