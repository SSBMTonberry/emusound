//
// Created by robin on 24.03.2020.
//

#ifndef EMUSOUND_EMUSTREAM_H
#define EMUSOUND_EMUSTREAM_H


#include "IEmu.h"
#include "IStream.h"

namespace esnd
{
    class IEmuStream : public IEmu, public IStream
    {

    };

    class EmuStream : public IEmuStream
    {
        public:
            void initialize(int track, uint32_t channelCount, uint32_t sampleRate) override
            {

            }

            void muteChannel(int channelNo, bool mute) override
            {

            }

            void setTempo(float tempo) override
            {

            }

            void setTrack(int track) override
            {

            }

            int getTimePlayed() const override
            {
                return 0;
            }

            void loadFromFile(const std::string &filename) override
            {

            }

            void loadFromMemory(void *data, size_t size) override
            {

            }

            void seek(int offset) override
            {

            }

        protected:
            size_t onRead(ma_decoder *pDecoder, void *pBufferOut, size_t bytesToRead) override
            {
                return 0;
            }

            ma_bool32 onSeek(ma_decoder *pDecoder, int byteOffset, ma_seek_origin origin) override
            {
                return 0;
            }
    };
}

#endif //EMUSOUND_EMUSTREAM_H
