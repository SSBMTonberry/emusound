//
// Created by robin on 01.05.2020.
//

#ifndef EMUSOUND_MUSICSTREAM_H
#define EMUSOUND_MUSICSTREAM_H

#include <mutex>
#include "ISoundStream.h"
#include "MusicConfig.hpp"
#include <functional>

namespace esnd
{
    namespace musiccb
    {
        inline void onDataCallback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount);
        //inline size_t onReadCallback(ma_decoder *pDecoder, void *pBufferOut, size_t bytesToRead);
        //inline ma_bool32 onSeekCallback(ma_decoder *pDecoder, int byteOffset, ma_seek_origin origin);
    }

    class MusicStream : public ISoundStream
    {
        public:
            MusicStream() = default;
            ~MusicStream();
            explicit MusicStream(const std::string &filename, uint32_t channels = 2, uint32_t sampleRate = 44100);
            MusicStream(void *data, size_t size, uint32_t channels = 2, uint32_t sampleRate = 44100);

            MusicStream(const std::string &id, const std::string &filename, uint32_t channels = 2, uint32_t sampleRate = 44100);
            MusicStream(const std::string &id, void *data, size_t size, uint32_t channels = 2, uint32_t sampleRate = 44100);

            StreamLoadStatus loadFromFile(const std::string &path, uint32_t channels, uint32_t sampleRate) override;
            StreamLoadStatus loadFromMemory(void *data, size_t size, uint32_t channels, uint32_t sampleRate) override;

            void play() override;
            void pause() override;
            void stop() override;
            void seek(int offset) override;

            friend void musiccb::onDataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
            //friend size_t musiccb::onReadCallback(ma_decoder* pDecoder, void* pBufferOut, size_t bytesToRead);
            //friend ma_bool32 musiccb::onSeekCallback(ma_decoder* pDecoder, int byteOffset, ma_seek_origin origin);

            void setVolume(float volume);

            uint32_t getChannelCount() const override;
            uint32_t getSampleRate() const override;
            SoundStatus getStatus() const override;
            float getVolume() const;
            float* getVolumePtr();

            StreamLoadStatus getLoadStatus() const;

            void onShutdown() override;

        protected:
            StreamLoadStatus initialize();

            void onGetData(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount) override;
            virtual size_t onRead(ma_decoder* pDecoder, void* pBufferOut, size_t bytesToRead)
            {
                return 0;
            }

            virtual ma_bool32 onSeek(ma_decoder* pDecoder, int byteOffset, ma_seek_origin origin)
            {
                return 0;
            }

            /*!
             * Samples to store in case they are to be exported to a file.
             */
            std::vector<short> m_samples;

            /*! Sample rate. 44100 is default and is the best quality. Anything below will take less space, but will
             *  also get worse quality on the sound. */
            uint32_t m_sampleRate;
            uint32_t m_channels;

            std::string m_filename; //if loaded by file
            void *m_data; //If loaded by memory
            size_t m_dataSize; //If loaded by memory

            int m_timePlayed = 0;
            bool m_isValid = true;
            float m_volume = 1.0;

            SoundStatus m_status;
            StreamMode m_loadMode;

            MusicConfig m_config;
            ma_result m_decoderInitStatus;
            std::mutex m_mutex; //Mutex for thread protection

            StreamLoadStatus m_loadStatus;
    };
}

#endif //EMUSOUND_MUSICSTREAM_H
