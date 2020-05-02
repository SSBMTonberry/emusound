//
// Created by robin on 27.03.2020.
//

#ifndef EMUSOUND_LOWPASSFILTER1_HPP
#define EMUSOUND_LOWPASSFILTER1_HPP

#include "ISoundFilter.h"

namespace esnd
{
    class LowpassFilter1 : public ISoundFilter
    {
        public:
            LowpassFilter1() = default;
            LowpassFilter1(const std::string &id, double cutoffFrequency, uint32_t channels = 2, uint32_t sampleRate = 44100)
            {
                init(id, cutoffFrequency, channels, sampleRate);
            }

            int init(const std::string &id, double cutoffFrequency, uint32_t channels = 2, uint32_t sampleRate = 44100)
            {
                m_id = id;
                config = ma_lpf1_config_init(ma_format_s16, channels, sampleRate, cutoffFrequency);
                return ma_lpf1_init(&config, &filter);
            }

            int refresh()
            {
                return ma_lpf1_init(&config, &filter);
            }

            int process(const void *input, size_t inputSize, void *output) override
            {
                if(isActive)
                {
                    return ma_lpf1_process_pcm_frames(&filter, output, input, inputSize);
                }
                return 0;
            }

            const std::string &getId() const override
            {
                return m_id;
            }

            const esnd::FilterType getFilterType() const override
            {
                return esnd::FilterType::LowpassFirstOrder;
            }

            ma_lpf1_config config;
            ma_lpf1 filter;

        private:
            std::string m_id = "default_lowpass1_id";
    };
}

#endif //EMUSOUND_LOWPASSFILTER1_HPP
