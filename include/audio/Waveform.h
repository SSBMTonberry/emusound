//
// Created by robin on 29.03.2020.
//

#ifndef EMUSOUND_WAVEFORM_H
#define EMUSOUND_WAVEFORM_H

#include <mutex>
#include "WaveformConfig.hpp"
#include <functional>
#include <vector>

namespace esnd
{
    namespace wavecb
    {
        inline void onDataCallback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount);
        //inline size_t onReadCallback(ma_decoder *pDecoder, void *pBufferOut, size_t bytesToRead);
        //inline ma_bool32 onSeekCallback(ma_decoder *pDecoder, int byteOffset, ma_seek_origin origin);
    }

    class Waveform
    {
        public:
            Waveform() = default;
            Waveform(const std::string &id, double amplitude, double frequency, WaveformType type, uint32_t channels = 2, uint32_t sampleRate = 44100);
            Waveform(double amplitude, double frequency, WaveformType type, uint32_t channels = 2, uint32_t sampleRate = 44100);

            StreamLoadStatus initialize(double amplitude, double frequency, WaveformType type, uint32_t channels = 2, uint32_t sampleRate = 44100);

            void play();
            void stop();
            void refresh();
            //void seek(int offset);

            void setId(const std::string &id);
            void setVolume(float volume);

            const std::string &getId() const;
            [[nodiscard]] SoundStatus getStatus() const;
            [[nodiscard]] uint32_t getChannelCount() const;
            [[nodiscard]] uint32_t getSampleRate() const;
            WaveformConfig *getConfig() { return &m_config; }
            float getVolume() const;
            float* getVolumePtr();

            friend void wavecb::onDataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
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
            float m_volume = 1.0;

            bool m_isValid = true;

            SoundStatus m_status;
            std::string m_id;


            WaveformConfig m_config;

            ma_result m_decoderInitStatus;

            //std::mutex m_mutex; //Mutex for thread protection
    };
}


#endif //EMUSOUND_WAVEFORM_H
