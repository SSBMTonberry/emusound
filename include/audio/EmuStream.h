//
// Created by robin on 25.03.2020.
//

#ifndef EMUSOUND_EMUSTREAM_H
#define EMUSOUND_EMUSTREAM_H

#include <mutex>
#include "ISoundStream.h"
#include "../data/EmuTrackInfo.h"
#include "EmuVoice.h"
#include "EmuConfig.hpp"
#include <functional>

namespace esnd
{
    namespace emucb
    {
        inline void onDataCallback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount);
        inline size_t onReadCallback(ma_decoder *pDecoder, void *pBufferOut, size_t bytesToRead);
        inline ma_bool32 onSeekCallback(ma_decoder *pDecoder, int byteOffset, ma_seek_origin origin);
    }
    class EmuStream : public ISoundStream
    {
        public:
            EmuStream() = default;
            ~EmuStream();
            EmuStream(const std::string &filename, int track = 0, uint32_t channels = 2, uint32_t sampleRate = 44100);
            EmuStream(void *data, size_t size, int track = 0, uint32_t channels = 2, uint32_t sampleRate = 44100);

            EmuStream(const std::string &id, const std::string &filename, int track = 0, uint32_t channels = 2, uint32_t sampleRate = 44100);
            EmuStream(const std::string &id, void *data, size_t size, int track = 0, uint32_t channels = 2, uint32_t sampleRate = 44100);

            void muteChannel(int channelNo, bool mute);

            void toggleMuteChannel(int channelNo);
            void unmuteAllChannels();

            void setTempo(float tempo);
            void setTrack(int track);
            //void setId(const std::string &id);
            void setNumberOfPlays(int numberOfPlays);
            void setVolume(float volume);

            void incrementNumberOfPlays();

            void nextTrack();
            void previousTrack();

            int getTimePlayed() const;
            int *getTimePlayedPtr();

            size_t getNumberOfVoices();
            std::vector<EmuVoice> *getVoices();
            const EmuTrackInfo &getInfoFromCurrentTrack() const;
            const std::vector<EmuTrackInfo> &getTracks() const;
            //EmuEqualizer *getEqualizer();

            StreamMode getLoadMode() const;
            const std::string &getFilename() const;
            int getTrack() const;
            void *getData() const;
            size_t getDataSize() const;
            int getNumberOfTracks() const;
            //const std::string &getId() const override;
            int getNumberOfPlays() const;
            const EmuConfig &getConfig() const;
            [[nodiscard]] SoundStatus getStatus() const override;
            [[nodiscard]] uint32_t getChannelCount() const override;
            [[nodiscard]] uint32_t getSampleRate() const override;

            StreamLoadStatus getLoadStatus() const;

            float getVolume() const;
            float* getVolumePtr();

            Music_Emu *getEmu() const;

            bool isValid() const;

            //Overridden
            esnd::StreamLoadStatus loadFromFile(const std::string &filename, int track, uint32_t channels = 2, uint32_t sampleRate = 44100);
            esnd::StreamLoadStatus loadFromMemory(void *data, size_t size, int track, uint32_t channels = 2, uint32_t sampleRate = 44100);

            esnd::StreamLoadStatus loadFromFile(const std::string &filename, uint32_t channels = 2, uint32_t sampleRate = 44100) override;
            esnd::StreamLoadStatus loadFromMemory(void *data, size_t size, uint32_t channels = 2, uint32_t sampleRate = 44100) override;

            void play() override;
            void pause() override;
            void stop() override;
            void seek(int offset) override;

            friend void emucb::onDataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
            friend size_t emucb::onReadCallback(ma_decoder* pDecoder, void* pBufferOut, size_t bytesToRead);
            friend ma_bool32 emucb::onSeekCallback(ma_decoder* pDecoder, int byteOffset, ma_seek_origin origin);

            void onShutdown() override;

        protected:
            StreamLoadStatus initialize();
            StreamLoadStatus initializeEmu();
            bool hasEmuError(gme_err_t emuError);

            size_t onRead(ma_decoder *pDecoder, void *pBufferOut, size_t bytesToRead) override;
            ma_bool32 onSeek(ma_decoder *pDecoder, int byteOffset, ma_seek_origin origin) override;
            void onGetData(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount) override;

            /*!
             * Samples to store in case they are to be exported to a file.
             */
            std::vector<short> m_samples;

            /*! Sample rate. 44100 is default and is the best quality. Anything below will take less space, but will
             *  also get worse quality on the sound. */
            uint32_t m_sampleRate;

            uint32_t m_channels;
            /*! The emulator for the sound*/
            Music_Emu *m_emu = nullptr;
            /*! The track loaded. 0 is the first track */
            int m_track = 0;


            std::string m_filename; //if loaded by file
            void *m_data; //If loaded by memory
            size_t m_dataSize; //If loaded by memory

            int m_timePlayed = 0;
            bool m_isValid = true;
            float m_volume = 1.0;

            int m_numberOfTracks = 0;
            std::vector<EmuVoice> m_voices;

            int m_numberOfPlays = 0;

            EmuTrackInfo m_emptyTrack; //When no track info exists
            std::vector<EmuTrackInfo> m_tracks;
            SoundStatus m_status;
            StreamMode m_loadMode;

            EmuConfig m_config;
            ma_result m_decoderInitStatus;

            std::mutex m_mutex; //Mutex for thread protection

            StreamLoadStatus m_loadStatus;
    };
}

#endif //EMUSOUND_EMUSTREAM_H
