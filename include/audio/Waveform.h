//
// Created by robin on 29.03.2020.
//

#ifndef EMUSOUND_WAVEFORM_H
#define EMUSOUND_WAVEFORM_H

#include <mutex>
#include "WaveformConfig.hpp"
#include <functional>

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
            ~Waveform();

            StreamLoadStatus initialize(uint32_t channels, uint32_t sampleRate, double amplitude, double frequency, WaveformType type);

            void play();
            void stop();
            //void seek(int offset);

            [[nodiscard]] SoundStatus getStatus() const;

            [[nodiscard]] uint32_t getChannelCount() const;
            [[nodiscard]] uint32_t getSampleRate() const;

            friend void wavecb::onDataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
            //friend size_t wavecb::onReadCallback(ma_decoder* pDecoder, void* pBufferOut, size_t bytesToRead);
            //friend ma_bool32 wavecb::onSeekCallback(ma_decoder* pDecoder, int byteOffset, ma_seek_origin origin);

        protected:

            //size_t onRead(ma_decoder *pDecoder, void *pBufferOut, size_t bytesToRead);
            //ma_bool32 onSeek(ma_decoder *pDecoder, int byteOffset, ma_seek_origin origin);
            //void onGetData(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount);

            /*!
             * Samples to store in case they are to be exported to a file.
             */
            std::vector<short> m_samples;

            /*! Sample rate. 44100 is default and is the best quality. Anything below will take less space, but will
             *  also get worse quality on the sound. */
            uint32_t m_sampleRate;

            uint32_t m_channels;

            bool m_isValid = true;
            bool m_isShuttingDown = false; //Set to true when calling destructor

            SoundStatus m_status;

            WaveformConfig m_config;
            ma_result m_decoderInitStatus;

            //std::mutex m_mutex; //Mutex for thread protection
    };
}


#endif //EMUSOUND_WAVEFORM_H
