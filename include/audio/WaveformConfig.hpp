//
// Created by robin on 29.03.2020.
//

#ifndef EMUSOUND_WAVEFORMCONFIG_HPP
#define EMUSOUND_WAVEFORMCONFIG_HPP

#include "external/emusound_external.h"
#include "../Enums.hpp"

namespace esnd
{
    class WaveformConfig
    {
        public:
            WaveformConfig() = default;
            WaveformConfig(uint32_t channels, uint32_t sampleRate, double amplitude, double frequency, WaveformType type)
            {
                initialize(channels, sampleRate, amplitude, frequency, type);
            }

            int initialize(uint32_t channels, uint32_t sampleRate, double amplitude, double frequency, WaveformType type)
            {
                config = ma_waveform_config_init(ma_format_f32, channels, sampleRate, (ma_waveform_type) type, amplitude, frequency);
                return ma_waveform_init(&config, &waveform);
            }

            ma_waveform waveform;
            ma_waveform_config config;
            ma_device_config deviceConfig;
            ma_device device;
    };
}

#endif //EMUSOUND_WAVEFORMCONFIG_HPP
