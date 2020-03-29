//
// Created by robin on 29.03.2020.
//

#ifndef EMUSOUND_BANDPASSFILTER_HPP
#define EMUSOUND_BANDPASSFILTER_HPP

#include "ISoundFilter.h"

namespace esnd
{
    class BandpassFilter : public ISoundFilter
    {
        public:
            BandpassFilter() = default;
            BandpassFilter(const std::string &id, double cutoffFrequency, double q, uint32_t channels = 2, uint32_t sampleRate = 44100)
            {
                init(id, cutoffFrequency, q, channels, sampleRate);
            }

            int init(const std::string &id, double cutoffFrequency, double q, uint32_t channels = 2, uint32_t sampleRate = 44100)
            {
                m_id = id;
                config = ma_bpf2_config_init(ma_format_s16, 2, 44100, cutoffFrequency, q);
                return ma_bpf2_init(&config, &filter);
            }

            int refresh()
            {
                return ma_bpf2_init(&config, &filter);
            }

            int process(const void *input, size_t inputSize, void *output) override
            {
                if(isActive)
                {
                    return ma_bpf2_process_pcm_frames(&filter, output, input, inputSize);
                }
                return 0;
            }

            const std::string &getId() const override
            {
                return m_id;
            }

            const FilterType getFilterType() const override
            {
                return FilterType::BandpassSecondOrder;
            }

            ma_bpf2_config config;
            ma_bpf2 filter;

        private:
            std::string m_id = "default_bandpass_id";
    };
}

#endif //EMUSOUND_BANDPASSFILTER_HPP
