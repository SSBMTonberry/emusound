//
// Created by robin on 28.03.2020.
//

#ifndef EMUSOUND_HIGHPASSFILTER1_HPP
#define EMUSOUND_HIGHPASSFILTER1_HPP

#include "ISoundFilter.h"

namespace esnd
{
    class HighpassFilter1 : public ISoundFilter
    {
        public:
            HighpassFilter1() = default;
            HighpassFilter1(ma_decoder *decoder, const std::string &id, double cutoffFrequency, uint32_t channels = 2, uint32_t sampleRate = 44100)
            {
                init(decoder, id, cutoffFrequency, channels, sampleRate);
            }

            int init(ma_decoder *decoder, const std::string &id, double cutoffFrequency, uint32_t channels = 2, uint32_t sampleRate = 44100)
            {
                m_decoder = decoder;
                m_id = id;
                config = ma_hpf1_config_init(m_decoder->outputFormat, channels, sampleRate, cutoffFrequency);
                return ma_hpf1_init(&config, &filter);
            }

            int refresh()
            {
                return ma_hpf1_init(&config, &filter);
            }

            int process(const void *input, size_t inputSize, void *output) override
            {
                if(isActive)
                {
                    return ma_hpf1_process_pcm_frames(&filter, output, input, inputSize);
                }
                return 0;
            }

            const std::string &getId() const override
            {
                return m_id;
            }

            const esnd::FilterType getFilterType() const override
            {
                return esnd::FilterType::HighpassFirstOrder;
            }

            ma_hpf1_config config;
            ma_hpf1 filter;

        private:
            std::string m_id = "default_highpass1_id";
    };
}

#endif //EMUSOUND_HIGHPASSFILTER1_HPP
