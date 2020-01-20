//
// Created by robin on 20.01.2020.
//

#ifndef EMUSOUND_EMUAUDIOSOURCE_H
#define EMUSOUND_EMUAUDIOSOURCE_H

#include <soloud/soloud.h>
class EmuAudioSource : public SoLoud::AudioSourceInstance
{
    public:


    private:
        unsigned int getAudio(float *aBuffer, unsigned int aSamplesToRead, unsigned int aBufferSize) override;

        bool hasEnded() override;

        SoLoud::result seek(SoLoud::time aSeconds, float *mScratch, unsigned int mScratchSize) override;

        SoLoud::result rewind() override;

        float getInfo(unsigned int aInfoKey) override;
};


#endif //EMUSOUND_EMUAUDIOSOURCE_H
