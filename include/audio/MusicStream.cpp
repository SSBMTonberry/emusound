//
// Created by robin on 01.05.2020.
//

#include "MusicStream.h"

void esnd::musiccb::onDataCallback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
{
    esnd::MusicStream *stream = (esnd::MusicStream*)pDevice->pUserData;
    if(stream == nullptr)
        return;

    if(stream->getStatus() == esnd::SoundStatus::Playing)
        stream->onGetData(pDevice, pOutput, pInput, frameCount);

    (void)pInput;
}


void esnd::MusicStream::onGetData(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    size_t bufferRead = ma_decoder_read_pcm_frames(&m_config.decoder, pOutput, frameCount);

    int filterStatus = processFilters(pOutput, bufferRead, pOutput);

    ma_apply_volume_factor_pcm_frames(pOutput, bufferRead, m_config.decoder.outputFormat, m_channels, m_volume);
}


esnd::MusicStream::MusicStream(const std::string &filename, uint32_t channels, uint32_t sampleRate)
{
    loadFromFile(filename, channels, sampleRate);
}

esnd::MusicStream::MusicStream(void *data, size_t size, uint32_t channels, uint32_t sampleRate)
{
    loadFromMemory(data, size, channels, sampleRate);
}

esnd::MusicStream::MusicStream(const std::string &id, const std::string &filename, uint32_t channels, uint32_t sampleRate)
{
    m_id = id;
    loadFromFile(filename, channels, sampleRate);
}

esnd::MusicStream::MusicStream(const std::string &id, void *data, size_t size, uint32_t channels, uint32_t sampleRate)
{
    m_id = id;
    loadFromMemory(data, size, channels, sampleRate);
}

esnd::MusicStream::~MusicStream()
{

}

esnd::StreamLoadStatus esnd::MusicStream::loadFromFile(const std::string &path, uint32_t channels, uint32_t sampleRate)
{
    m_loadMode = StreamMode::File;
    m_filename = path;
    m_channels = channels;
    m_sampleRate = sampleRate;
    return initialize();
}

esnd::StreamLoadStatus esnd::MusicStream::loadFromMemory(void *data, size_t size, uint32_t channels, uint32_t sampleRate)
{
    m_loadMode = StreamMode::Memory;
    m_data = data;
    m_dataSize = size;
    m_channels = channels;
    m_sampleRate = sampleRate;
    return initialize();
}

esnd::StreamLoadStatus esnd::MusicStream::initialize()
{
    m_config.initialize(m_channels, m_sampleRate);

    //m_decoderInitStatus = ma_decoder_init_raw(esnd::musiccb::onReadCallback, esnd::musiccb::onSeekCallback, &m_config.decoder,
    //                                          &m_config.dec_config_in, &m_config.dec_config_out, &m_config.decoder);

    if(m_loadMode == StreamMode::File)
        m_decoderInitStatus = ma_decoder_init_file(m_filename.c_str(), &m_config.dec_config, &m_config.decoder);
    else
        m_decoderInitStatus = ma_decoder_init_memory(m_data, m_dataSize, &m_config.dec_config, &m_config.decoder);

    if (m_decoderInitStatus != MA_SUCCESS) {
        return esnd::StreamLoadStatus::DecoderInitError;
    }

    m_config.deviceConfig = ma_device_config_init(ma_device_type_playback);
    m_config.deviceConfig.playback.format   = m_config.decoder.outputFormat;
    m_config.deviceConfig.playback.channels = m_config.decoder.outputChannels;
    m_config.deviceConfig.sampleRate        = m_config.decoder.outputSampleRate;
    m_config.deviceConfig.dataCallback      = esnd::musiccb::onDataCallback;
    m_config.deviceConfig.pUserData         = &m_config.decoder; //this;
    m_config.deviceConfig.pUserData         = this; //&m_config.decoder; //this;
    //m_config.deviceConfig.stopCallback      = onStop;

    if (ma_device_init(NULL, &m_config.deviceConfig, &m_config.device) != MA_SUCCESS) {
        printf("Failed to open playback device.\n");
        ma_decoder_uninit(&m_config.decoder);
        return esnd::StreamLoadStatus::StreamOpenFailure;
    }

    if (ma_device_start(&m_config.device) != MA_SUCCESS) {
        printf("Failed to start playback device.\n");
        ma_device_uninit(&m_config.device);
        ma_decoder_uninit(&m_config.decoder);
        return esnd::StreamLoadStatus::StreamStartFailure;
    }

    return esnd::StreamLoadStatus::OK;
}

void esnd::MusicStream::play()
{
    m_status = SoundStatus::Playing;
}

void esnd::MusicStream::pause()
{
    m_status = SoundStatus::Paused;
}

void esnd::MusicStream::stop()
{
    m_status = SoundStatus::Stopped;
    seek(0);
}

void esnd::MusicStream::seek(int offset)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    uint32_t toSeek = m_config.dec_config.sampleRate * (offset / 1000);
    ma_decoder_seek_to_pcm_frame(&m_config.decoder, toSeek);
}

uint32_t esnd::MusicStream::getChannelCount() const
{
    return m_channels;
}

uint32_t esnd::MusicStream::getSampleRate() const
{
    return m_sampleRate;
}

esnd::SoundStatus esnd::MusicStream::getStatus() const
{
    return m_status;
}

void esnd::MusicStream::onShutdown()
{
    ma_mutex_uninit(&m_config.device.lock);
    ma_device_uninit(&m_config.device);
    ma_context_uninit(m_config.device.pContext);
    ma_decoder_uninit(&m_config.decoder);
}

void esnd::MusicStream::setVolume(float volume)
{
    m_volume = volume;
}

float esnd::MusicStream::getVolume() const
{
    return m_volume;
}

float *esnd::MusicStream::getVolumePtr()
{
    return &m_volume;
}
