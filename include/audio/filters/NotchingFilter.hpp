//
// Created by robin on 29.03.2020.
//

#ifndef EMUSOUND_NOTCHINGFILTER_HPP
#define EMUSOUND_NOTCHINGFILTER_HPP

#include "ISoundFilter.h"

namespace esnd
{
    class NotchingFilter : public ISoundFilter
    {
        public:
            NotchingFilter() = default;
            NotchingFilter(const std::string &id, double q, double frequency, uint32_t channels = 2, uint32_t sampleRate = 44100)
            {
                init(id, q, frequency, channels, sampleRate);
            }

            int init(const std::string &id, double q, double frequency, uint32_t channels = 2, uint32_t sampleRate = 44100)
            {
                m_id = id;
                config = ma_notch2_config_init(ma_format_s16, channels, sampleRate, q, frequency);
                return ma_notch2_init(&config, &filter);
            }

            int refresh()
            {
                return ma_notch2_init(&config, &filter);
            }

            int process(const void *input, size_t inputSize, void *output) override
            {
                if(isActive)
                {
                    return ma_notch2_process_pcm_frames(&filter, output, input, inputSize);
                }
                return 0;
            }

            const std::string &getId() const override
            {
                return m_id;
            }

            const FilterType getFilterType() const override
            {
                return FilterType::NotchingSecondOrder;
            }

            ma_notch2_config config;
            ma_notch2 filter;

        private:
            std::string m_id = "default_notching_id";
    };
}

#endif //EMUSOUND_NOTCHINGFILTER_HPP
