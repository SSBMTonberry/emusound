//
// Created by robin on 24.03.2020.
//

#ifndef EMUSOUND_IEMU_H
#define EMUSOUND_IEMU_H

#include "libgme/gme.h"
#include "libgme/Music_Emu.h"

#include <stdio.h>
#include <vector>
#include <string>

namespace esnd
{
    class IEmu
    {
        public:
            virtual void initialize(int track = 0, uint32_t channelCount = 2, uint32_t sampleRate = 44100) = 0;
            virtual void muteChannel(int channelNo, bool mute) = 0;
            virtual void setTempo(float tempo) = 0;
            virtual void setTrack(int track) = 0;
            virtual int getTimePlayed() const = 0;
    };
}

#endif //EMUSOUND_IEMU_H
