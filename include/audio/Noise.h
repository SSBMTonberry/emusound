//
// Created by robin on 02.04.2020.
//

#ifndef EMUSOUND_NOISE_H
#define EMUSOUND_NOISE_H
#include <mutex>
#include "NoiseConfig.hpp"
#include <functional>
namespace esnd
{
    namespace noisecb
    {
        inline void onDataCallback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount);
        //inline size_t onReadCallback(ma_decoder *pDecoder, void *pBufferOut, size_t bytesToRead);
        //inline ma_bool32 onSeekCallback(ma_decoder *pDecoder, int byteOffset, ma_seek_origin origin);
    }

    class Noise
    {
        public:
            Noise() = default;
            Noise(const std::string &id, int32_t seed, double amplitude, WaveformType type, uint32_t channels = 2, uint32_t sampleRate = 44100);
            Noise(int32_t seed, double amplitude, WaveformType type, uint32_t channels = 2, uint32_t sampleRate = 44100);

            StreamLoadStatus initialize(double amplitude, double frequency, WaveformType type, uint32_t channels = 2, uint32_t sampleRate = 44100);

            void play();
            void stop();
            void refresh();
            //void seek(int offset);

            void setId(const std::string &id);

            const std::string &getId() const;
            [[nodiscard]] SoundStatus getStatus() const;
            [[nodiscard]] uint32_t getChannelCount() const;
            [[nodiscard]] uint32_t getSampleRate() const;
            NoiseConfig *getConfig() { return &m_config; }

            friend void noisecb::onDataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
            void onShutdown();

        protected:

            //size_t onRead(ma_decoder *pDecoder, void *pBufferOut, size_t bytesToRead);
            //ma_bool32 onSeek(ma_decoder *pDecoder, int byteOffset, ma_seek_origin origin);
            void onGetData(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount);

            /*!
             * Samples to store in case they are to be exported to a file.
             */
            std::vector<short> m_samples;

            /*! Sample rate. 44100 is default and is the best quality. Anything below will take less space, but will
             *  also get worse quality on the sound. */
            uint32_t m_sampleRate;

            uint32_t m_channels;

            bool m_isValid = true;

            SoundStatus m_status;
            std::string m_id;

            NoiseConfig m_config;

            ma_result m_decoderInitStatus;

            //std::mutex m_mutex; //Mutex for thread protection
    };
}

#endif //EMUSOUND_NOISE_H
