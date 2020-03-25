//
// Created by robin on 25.03.2020.
//

#include "EmuStream.h"

esnd::EmuStream::EmuStream()
{

}

esnd::EmuStream::EmuStream(const std::string &filename, int track, uint32_t channels, uint32_t sampleRate)
{
    loadFromFile(filename, track, channels, sampleRate);
}

esnd::EmuStream::EmuStream(void *data, size_t size, int track, uint32_t channels, uint32_t sampleRate)
{
    loadFromMemory(data, size, track, channels, sampleRate);
}

void esnd::EmuStream::initialize()
{
    //std::bind(&esnd::EmuStream::onRead, this, std::placeholders::_1, std::placeholders::_2,
    //            std::placeholders::_3)
    //std::function<size_t(ma_decoder *,void *,size_t)> on_read = &esnd::EmuStream::onRead;
    //std::function<ma_bool32(ma_decoder *,int,ma_seek_origin)> on_seek = &esnd::EmuStream::onSeek;

    m_decoderInitStatus = ma_decoder_init_raw(&esnd::EmuStream::onRead, &esnd::EmuStream::onSeek, &m_config.decoder,
            &m_config.dec_config_in, &m_config.dec_config_out, &m_config.decoder);
    m_config.deviceConfig = ma_device_config_init(ma_device_type_playback);
    m_config.deviceConfig.playback.format   = decoder.outputFormat;
    m_config.deviceConfig.playback.channels = decoder.outputChannels;
    m_config.deviceConfig.sampleRate        = decoder.outputSampleRate;
    m_config.deviceConfig.dataCallback      = onGetData;
    m_config.deviceConfig.pUserData         = &decoder;

}

void esnd::EmuStream::muteChannel(int channelNo, bool mute)
{
    if(channelNo < m_voices.size())
    {
        m_voices[channelNo].setMuted(mute);
        m_emu->mute_voice(channelNo, mute);
    }
}

void esnd::EmuStream::toggleMuteChannel(int channelNo)
{
    if(channelNo < m_voices.size())
    {
        m_voices[channelNo].toggleMute();
        m_emu->mute_voice(channelNo, m_voices[channelNo].isMuted());
    }
}

void esnd::EmuStream::unmuteAllChannels()
{
    m_emu->mute_voices(0);
    for(auto const &channel : m_voices)
    {
        muteChannel(channel.getChannelNo(), false);
    }
}

void esnd::EmuStream::setTempo(float tempo)
{
    if(m_emu != nullptr)
    {
        m_tracks[m_track].setTempo(tempo);
        m_emu->set_tempo(tempo);
    }
}

void esnd::EmuStream::setTrack(int track)
{
    m_track = track;
    if(m_emu != nullptr)
    {
        m_emu->start_track(m_track);
        //handleError(m_emu->start_track(m_track));
    }
}

void esnd::EmuStream::setId(const std::string &id)
{
    m_id = id;
}

void esnd::EmuStream::setNumberOfPlays(int numberOfPlays)
{
    m_numberOfPlays = numberOfPlays;
}

void esnd::EmuStream::incrementNumberOfPlays()
{
    ++m_numberOfPlays;
}

void esnd::EmuStream::nextTrack()
{
    m_track = ((m_track + 1) > m_numberOfTracks - 1) ? 0 : m_track + 1;
    setTrack(m_track);
}

void esnd::EmuStream::previousTrack()
{
    m_track = ((m_track-1 < 0) && m_numberOfTracks > 0) ? m_numberOfTracks - 1 : m_track - 1;
    setTrack(m_track);
}

int esnd::EmuStream::getTimePlayed() const
{
    return m_timePlayed;
}

int *esnd::EmuStream::getTimePlayedPtr()
{
    return &m_timePlayed;
}

size_t esnd::EmuStream::getNumberOfVoices()
{
    return m_voices.size();
}

std::vector<esnd::EmuVoice> *esnd::EmuStream::getVoices()
{
    return &m_voices;
}

const esnd::EmuTrackInfo &esnd::EmuStream::getInfoFromCurrentTrack() const
{
    return (m_numberOfTracks > 0) ? m_tracks[m_track] : m_emptyTrack;
}

const std::vector<esnd::EmuTrackInfo> &esnd::EmuStream::getTracks() const
{
    return m_tracks;
}

//EmuEqualizer *getEqualizer()
// {


esnd::StreamMode esnd::EmuStream::getLoadMode() const
{
    return m_loadMode;
}

const std::string &esnd::EmuStream::getFilename() const
{
    return m_filename;
}

int esnd::EmuStream::getTrack() const
{
    return m_track;
}

void *esnd::EmuStream::getData() const
{
    return m_data;
}

size_t esnd::EmuStream::getDataSize() const
{
    return m_dataSize;
}

int esnd::EmuStream::getNumberOfTracks() const
{
    return m_numberOfTracks;
}

const std::string &esnd::EmuStream::getId() const
{
    return m_id;
}

int esnd::EmuStream::getNumberOfPlays() const
{
    return m_numberOfPlays;
}

bool esnd::EmuStream::isValid() const
{
    return m_isValid;
}

//Overridden

void esnd::EmuStream::loadFromFile(const std::string &filename, int track, uint32_t channels, uint32_t sampleRate)
{
    m_track = track;
    loadFromFile(filename, channels, sampleRate);
}

void esnd::EmuStream::loadFromMemory(void *data, size_t size, int track, uint32_t channels, uint32_t sampleRate)
{
    m_track = track;
    loadFromMemory(data, size, channels, sampleRate);
}

void esnd::EmuStream::loadFromFile(const std::string &filename, uint32_t channels, uint32_t sampleRate)
{
    m_filename = filename;
    m_channels = channels;
    m_sampleRate = sampleRate;
    initialize();
}

void esnd::EmuStream::loadFromMemory(void *data, size_t size, uint32_t channels, uint32_t sampleRate)
{
    m_data = data;
    m_dataSize = size;
    m_channels = channels;
    m_sampleRate = sampleRate;
    initialize();
}

void esnd::EmuStream::play()
{
    m_status = SoundStatus::Playing;
}

void esnd::EmuStream::pause()
{
    m_status = SoundStatus::Paused;
}

void esnd::EmuStream::stop()
{
    m_status = SoundStatus::Stopped;
}

void esnd::EmuStream::seek(int offset)
{
    ma_decoder_seek_to_pcm_frame(&m_decoder, offset);
}

esnd::SoundStatus esnd::EmuStream::getStatus() const
{
    return SoundStatus::Stopped;
}

size_t esnd::EmuStream::onRead(ma_decoder *pDecoder, void *pBufferOut, size_t bytesToRead)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    size_t bufferSize = bytesToRead / 2;

    m_emu->play(bufferSize, (short*) pBufferOut);
    //ma_lpf1_process_pcm_frames(&lowpass_filter, pBufferOut, pBufferOut, bufferSize);

    return bufferSize;
}

ma_bool32 esnd::EmuStream::onSeek(ma_decoder *pDecoder, int byteOffset, ma_seek_origin origin)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    int toSeek = byteOffset / 4;
    blargg_err_t error = m_emu->seek(toSeek);

    return (error) ? false : true;
}

void esnd::EmuStream::onGetData(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) {
        return;
    }

    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount);

    (void)pInput;
}

uint32_t esnd::EmuStream::getChannelCount() const
{
    return m_channels;
}

uint32_t esnd::EmuStream::getSampleRate() const
{
    return m_sampleRate;
}


