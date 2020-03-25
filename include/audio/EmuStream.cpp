//
// Created by robin on 25.03.2020.
//

#include "EmuStream.h"

void esnd::EmuStream::loadFromFile(const std::string &filename, uint32_t channelCount, uint32_t sampleRate)
{

}

void esnd::EmuStream::loadFromMemory(void *data, size_t size, uint32_t channelCount, uint32_t sampleRate)
{

}

void esnd::EmuStream::play()
{

}

void esnd::EmuStream::pause()
{

}

void esnd::EmuStream::stop()
{

}

void esnd::EmuStream::seek(int offset)
{

}

esnd::SoundStatus esnd::EmuStream::getStatus() const
{
    return SoundStatus::Stopped;
}

size_t esnd::EmuStream::onRead(ma_decoder *pDecoder, void *pBufferOut, size_t bytesToRead)
{
    return 0;
}

ma_bool32 esnd::EmuStream::onSeek(ma_decoder *pDecoder, int byteOffset, ma_seek_origin origin)
{
    return false;
}

uint32_t esnd::EmuStream::getChannelCount() const
{
    return 0;
}

uint32_t esnd::EmuStream::getSampleRate() const
{
    return 0;
}


