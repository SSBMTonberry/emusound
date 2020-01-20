//
// Created by robin on 20.01.2020.
//

#include "EmuAudioSource.h"

unsigned int EmuAudioSource::getAudio(float *aBuffer, unsigned int aSamplesToRead, unsigned int aBufferSize)
{
    return 0;
}

bool EmuAudioSource::hasEnded()
{
    return false;
}

SoLoud::result EmuAudioSource::seek(SoLoud::time aSeconds, float *mScratch, unsigned int mScratchSize)
{
    return AudioSourceInstance::seek(aSeconds, mScratch, mScratchSize);
}

SoLoud::result EmuAudioSource::rewind()
{
    return AudioSourceInstance::rewind();
}

float EmuAudioSource::getInfo(unsigned int aInfoKey)
{
    return AudioSourceInstance::getInfo(aInfoKey);
}
