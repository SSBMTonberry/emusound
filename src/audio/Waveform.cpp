//
// Created by robin on 29.03.2020.
//

#include "audio/Waveform.h"

esnd::Waveform::~Waveform()
{
    m_isShuttingDown = true;
    ma_device_uninit(&m_config.device);
}

void esnd::wavecb::onDataCallback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
{
    esnd::Waveform* waveform = (esnd::Waveform*)pDevice->pUserData;

    if(waveform && waveform->getStatus() == esnd::SoundStatus::Playing)
        ma_waveform_read_pcm_frames(&waveform->m_config.waveform, pOutput, frameCount);

    (void)pInput; /* Unused. */
}

esnd::StreamLoadStatus esnd::Waveform::initialize(uint32_t channels, uint32_t sampleRate, double amplitude, double frequency, esnd::WaveformType type)
{
    esnd::StreamLoadStatus status = esnd::StreamLoadStatus::OK;
    if(m_config.initialize(channels, sampleRate, amplitude, frequency, type) != 0)
        return esnd::StreamLoadStatus::WaveformInitError;

    m_config.deviceConfig = ma_device_config_init(ma_device_type_playback);
    m_config.deviceConfig.playback.format   = m_config.config.format;
    m_config.deviceConfig.playback.channels = m_config.config.channels;
    m_config.deviceConfig.sampleRate        = m_config.config.sampleRate;
    m_config.deviceConfig.dataCallback      = esnd::wavecb::onDataCallback;
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

void esnd::Waveform::play()
{
    m_status = esnd::SoundStatus::Playing;
}

void esnd::Waveform::stop()
{
    m_status = esnd::SoundStatus::Stopped;
}

esnd::SoundStatus esnd::Waveform::getStatus() const
{
    return m_status;
}

uint32_t esnd::Waveform::getChannelCount() const
{
    return m_channels;
}

uint32_t esnd::Waveform::getSampleRate() const
{
    return m_sampleRate;
}
