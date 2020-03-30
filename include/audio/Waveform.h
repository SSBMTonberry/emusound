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
            static constexpr double A1 = 27.5;
            static constexpr double A1_SHARP = 29.135;
            static constexpr double B1 = 30.863;

            Waveform() = default;
            Waveform(const std::string &id, double amplitude, double frequency, WaveformType type, uint32_t channels = 2, uint32_t sampleRate = 44100);
            Waveform(double amplitude, double frequency, WaveformType type, uint32_t channels = 2, uint32_t sampleRate = 44100);
            ~Waveform();

            StreamLoadStatus initialize(double amplitude, double frequency, WaveformType type, uint32_t channels = 2, uint32_t sampleRate = 44100);

            void play();
            void stop();
            void refresh();
            //void seek(int offset);

            const std::string &getId() const;
            [[nodiscard]] SoundStatus getStatus() const;
            [[nodiscard]] uint32_t getChannelCount() const;
            [[nodiscard]] uint32_t getSampleRate() const;
            WaveformConfig *getConfig() { return &m_config; }


            void setId(const std::string &id);

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
            std::string m_id;

            WaveformConfig m_config;
            ma_result m_decoderInitStatus;

            //std::mutex m_mutex; //Mutex for thread protection
    };
}


#endif //EMUSOUND_WAVEFORM_H
