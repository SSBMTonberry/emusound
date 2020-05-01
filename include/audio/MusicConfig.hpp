//
// Created by robin on 01.05.2020.
//

#ifndef EMUSOUND_MUSICCONFIG_HPP
#define EMUSOUND_MUSICCONFIG_HPP

namespace esnd
{
    class MusicConfig
    {
        public:
            MusicConfig() = default;
            MusicConfig(uint32_t channels, uint32_t sampleRate)
            {
                initialize(channels, sampleRate);
            }

            void initialize(uint32_t channels, uint32_t sampleRate)
            {
                dec_config = ma_decoder_config_init(ma_format_s16, channels, sampleRate);
                //dec_config = ma_decoder_config_init(ma_format_f32, channels, sampleRate);
                //dec_config_in = ma_decoder_config_init(ma_format_s16, channels, sampleRate);
                //dec_config_out = ma_decoder_config_init(ma_format_s16, channels, sampleRate);
            }

            ma_decoder decoder;
            ma_decoder_config dec_config;
            //ma_decoder_config dec_config_in;
            //ma_decoder_config dec_config_out;
            ma_device_config deviceConfig;
            ma_device device;
    };
}

#endif //EMUSOUND_MUSICCONFIG_HPP
