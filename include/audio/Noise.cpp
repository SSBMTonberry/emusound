//
// Created by robin on 02.04.2020.
//

#include "Noise.h"

void esnd::noisecb::onDataCallback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
{
    esnd::Noise* noise = (esnd::Noise*)pDevice->pUserData;

    if(noise && noise->getStatus() == esnd::SoundStatus::Playing)
        noise->onGetData(pDevice, pOutput, pInput, frameCount);

    (void)pInput; /* Unused. */
}

esnd::Noise::Noise(const std::string &id, int32_t seed, double amplitude, esnd::NoiseType type, uint32_t channels) : m_id {id}
{
    initialize(seed, amplitude, type, channels); //, sampleRate);
}

esnd::Noise::Noise(int32_t seed, double amplitude, esnd::NoiseType type, uint32_t channels)//, uint32_t sampleRate)
{
    initialize(seed, amplitude, type, channels); //, sampleRate);
}

esnd::StreamLoadStatus esnd::Noise::initialize(int32_t seed, double amplitude, esnd::NoiseType type, uint32_t channels)
{
    esnd::StreamLoadStatus status = esnd::StreamLoadStatus::OK;
    if(m_config.initialize(channels, seed, amplitude, type) != 0)
        return esnd::StreamLoadStatus::WaveformInitError;

    m_config.deviceConfig = ma_device_config_init(ma_device_type_playback);
    m_config.deviceConfig.playback.format   = m_config.config.format;
    m_config.deviceConfig.playback.channels = m_config.config.channels;
    m_config.deviceConfig.sampleRate        = 44100; //m_config.config.;
    m_config.deviceConfig.dataCallback      = esnd::noisecb::onDataCallback;
    m_config.deviceConfig.pUserData         = this;//&m_config.decoder;

    if (ma_device_init(NULL, &m_config.deviceConfig, &m_config.device) != MA_SUCCESS) {
        printf("Failed to open playback device.\n");

        return esnd::StreamLoadStatus::WaveformDeviceError;
    }

    if (ma_device_start(&m_config.device) != MA_SUCCESS) {
        printf("Failed to start playback device.\n");
        ma_device_uninit(&m_config.device);
        return esnd::StreamLoadStatus::WaveformStartupFailure;
    }

    return status;
}

void esnd::Noise::play()
{
    m_status = esnd::SoundStatus::Playing;
}

void esnd::Noise::stop()
{
    m_status = esnd::SoundStatus::Stopped;
}

void esnd::Noise::refresh()
{
    m_config.refresh();
}

void esnd::Noise::setId(const std::string &id)
{
    m_id = id;
}

const std::string &esnd::Noise::getId() const
{
    return m_id;
}

esnd::SoundStatus esnd::Noise::getStatus() const
{
    return m_status;
}

uint32_t esnd::Noise::getChannelCount() const
{
    return m_channels;
}

uint32_t esnd::Noise::getSampleRate() const
{
    return m_sampleRate;
}

void esnd::Noise::onShutdown()
{
    ma_device_uninit(&m_config.device);
}

void esnd::Noise::onGetData(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
{
    ma_noise_read_pcm_frames(&m_config.noise, pOutput, frameCount);
    ma_apply_volume_factor_pcm_frames(pOutput, frameCount, ma_format_f32, 2, m_volume);
}

float esnd::Noise::getVolume() const
{
    return m_volume;
}

void esnd::Noise::setVolume(float volume)
{
    m_volume = volume;
}

float *esnd::Noise::getVolumePtr()
{
    return &m_volume;
}


