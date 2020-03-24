//
// Created by robin on 24.03.2020.
//

#ifndef EMUSOUND_ISTREAM_H
#define EMUSOUND_ISTREAM_H


#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "libgme/gme.h"
#include "libgme/Music_Emu.h"

#include <stdio.h>
#include <vector>
#include <string>

namespace esnd
{
    class IStream
    {
        public:
            virtual void loadFromFile(const std::string &filename) = 0;
            virtual void loadFromMemory(void *data, size_t size) = 0;
            virtual void seek(int offset) = 0;

        protected:
            virtual size_t onRead(ma_decoder* pDecoder, void* pBufferOut, size_t bytesToRead) = 0;
            virtual ma_bool32 onSeek(ma_decoder* pDecoder, int byteOffset, ma_seek_origin origin) = 0;
    };
}

#endif //EMUSOUND_ISTREAM_H
