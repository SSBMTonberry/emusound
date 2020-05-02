//
// Created by robin on 28.03.2020.
//

#ifndef EMUSOUND_HIGHPASSFILTER2_HPP
#define EMUSOUND_HIGHPASSFILTER2_HPP

#include "ISoundFilter.h"

namespace esnd
{
    class HighpassFilter2 : public ISoundFilter
    {
        public:
            HighpassFilter2() = default;
            HighpassFilter2(ma_decoder *decoder, const std::string &id, double cutoffFrequency, double q, uint32_t channels = 2, uint32_t sampleRate = 44100)
            {
                init(decoder, id, cutoffFrequency, q, channels, sampleRate);
            }

            int init(ma_decoder *decoder, const std::string &id, double cutoffFrequency, double q, uint32_t channels = 2, uint32_t sampleRate = 44100)
            {
                m_decoder = decoder;
                m_id = id;
                config = ma_hpf2_config_init(m_decoder->outputFormat, channels, sampleRate, cutoffFrequency, q);
                return ma_hpf2_init(&config, &filter);
            }

            int refresh()
            {
                return ma_hpf2_init(&config, &filter);
            }

            int process(const void *input, size_t inputSize, void *output) override
            {
                if(isActive)
                {
                    return ma_hpf2_process_pcm_frames(&filter, output, input, inputSize);
                }
                return 0;
            }

            const std::string &getId() const override
            {
                return m_id;
            }

            const FilterType getFilterType() const override
            {
                return FilterType::HighpassSecondOrder;
            }

            ma_hpf2_config config;
            ma_hpf2 filter;

        private:
            std::string m_id = "default_highpass2_id";
    };
}

#endif //EMUSOUND_HIGHPASSFILTER2_HPP
