//
// Created by robin on 24.03.2020.
//

#ifndef EMUSOUND_ISOUNDSTREAM_H
#define EMUSOUND_ISOUNDSTREAM_H

#include "libgme/gme.h"
#include "libgme/Music_Emu.h"

#include <stdio.h>
#include <vector>
#include <string>

#include "Enums.hpp"
#include "../external/emusound_external.h"

namespace esnd
{
    class ISoundStream
    {
        public:
            /*!
             * Load from file.
             *
             * @param path Path to file
             * @param channels 1 = Mono, 2 = Stereo
             * @param sampleRate 44100 is optimal for best quality. Anything less will decrease the sound quality.
             */
            virtual esnd::StreamLoadStatus loadFromFile(const std::string &path, uint32_t channels, uint32_t sampleRate) = 0;

            /*!
             * Load from memory.
             *
             * @param data The data stored in memory
             * @param size The size of the data stored in memory
             * @param channels 1 = Mono, 2 = Stereo
             * @param sampleRate 44100 is optimal for best quality. Anything less will decrease the sound quality.
             */
            virtual esnd::StreamLoadStatus loadFromMemory(void *data, size_t size, uint32_t channels, uint32_t sampleRate) = 0;

            virtual void play() = 0;
            virtual void pause() = 0;
            virtual void stop() = 0;
            virtual void seek(int offset) = 0;

            [[nodiscard]] virtual uint32_t getChannelCount() const = 0;
            [[nodiscard]] virtual uint32_t getSampleRate() const = 0;

            [[nodiscard]] virtual SoundStatus getStatus() const = 0;

        protected:
            virtual size_t onRead(ma_decoder* pDecoder, void* pBufferOut, size_t bytesToRead) = 0;
            virtual ma_bool32 onSeek(ma_decoder* pDecoder, int byteOffset, ma_seek_origin origin) = 0;
            virtual void onGetData(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) = 0;
    };
}

#endif //EMUSOUND_ISOUNDSTREAM_H
