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
    fpSetTolerance = (fptypeSetTolerance)abLibrary.getFunction("aubio_pitch_set_tolerance");
    fpSetSilence = (fptypeSetSilence)abLibrary.getFunction("aubio_pitch_get_silence");
    fpGetConfidence = (fptypeGetConfidence)abLibrary.getFunction("aubio_pitch_get_confidence");
    fpGetLoudness = (fptypeGetLoudness)abLibrary.getFunction("aubio_db_spl");
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

    DBG(aubio_db_spl(&aubioInput));

    fpAubioPitchDo(aubioPitch.get(), &aubioInput, &aubioOutput);
    result.confidence = fpGetConfidence(aubioPitch.get());
    result.loudness = fpGetLoudness(&aubioInput);
    
    return result;
}

uint_t AubioHandler::setTolerance(smpl_t tol)
{
    return fpSetTolerance(aubioPitch.get(), tol);
}

uint_t AubioHandler::setSilence(smpl_t sil)
{
    return fpSetSilence(aubioPitch.get(), sil);
}

void AubioHandler::PitchDeleter::operator()(aubio_pitch_t * p)
{
    AubioHandler::getInstance().fpDelAubioPitch(p);
}
