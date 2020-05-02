//
// Created by robin on 29.03.2020.
//

#ifndef EMUSOUND_PEAKINGEQFILTER_HPP
#define EMUSOUND_PEAKINGEQFILTER_HPP

#include "ISoundFilter.h"

namespace esnd
{
    class PeakingEqFilter : public ISoundFilter
    {
        public:
            PeakingEqFilter() = default;
            PeakingEqFilter(const std::string &id, double gainDb, double q, double frequency, uint32_t channels = 2, uint32_t sampleRate = 44100)
            {
                init(id, gainDb, q, frequency, channels, sampleRate);
            }

            int init(const std::string &id, double gainDb, double q, double frequency, uint32_t channels = 2, uint32_t sampleRate = 44100)
            {
                m_id = id;
                config = ma_peak2_config_init(ma_format_s16, channels, sampleRate, gainDb, q, frequency);
                return ma_peak2_init(&config, &filter);
            }

            int refresh()
            {
                return ma_peak2_init(&config, &filter);
            }

            int process(const void *input, size_t inputSize, void *output) override
            {
                if(isActive)
                {
                    return ma_peak2_process_pcm_frames(&filter, output, input, inputSize);
                }
                return 0;
            }

            const std::string &getId() const override
            {
                return m_id;
            }

            const FilterType getFilterType() const override
            {
                return FilterType::PeakingEqSecondOrder;
            }

            ma_peak2_config config;
            ma_peak2 filter;

        private:
            std::string m_id = "default_peakingeq_id";
    };
}

#endif //EMUSOUND_PEAKINGEQFILTER_HPP
