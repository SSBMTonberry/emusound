//
// Created by robin on 02.04.2020.
//

#ifndef EMUSOUND_NOISECONFIG_HPP
#define EMUSOUND_NOISECONFIG_HPP
#include "external/emusound_external.h"
#include "../Enums.hpp"

namespace esnd
{
    class NoiseConfig
    {
        public:
            NoiseConfig() = default;
            NoiseConfig(uint32_t channels, int32_t seed, double amplitude, WaveformType type)
            {
                initialize(channels, seed, amplitude, type);
            }

            int initialize(uint32_t channels, int32_t seed, double amplitude, WaveformType type)
            {
                config = ma_noise_config_init(ma_format_f32, channels, (ma_noise_type) type, seed, amplitude);
                return ma_noise_init(&config, &waveform);
            }

            int refresh()
            {
                return ma_noise_init(&config, &waveform);
            }

            ma_noise waveform;
            ma_noise_config config;
            ma_device_config deviceConfig;
            ma_device device;
    };
}

#endif //EMUSOUND_NOISECONFIG_HPP
