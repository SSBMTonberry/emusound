//
// Created by robin on 28.03.2020.
//

#ifndef EMUSOUND_BIQUADFILTER_HPP
#define EMUSOUND_BIQUADFILTER_HPP

#include "ISoundFilter.h"

namespace esnd
{
    class BiquadFilter : public ISoundFilter
    {
        public:
            BiquadFilter() = default;
            BiquadFilter(const std::string &id, double b0 = 1, double b1 = 1, double b2 = 1, double a0 = 1, double a1 = 1, double a2 = 1, uint32_t channels = 2)
            {
                init(id, b0, b1, b2, a0, a1, a2, channels);
            }

            int init(const std::string &id, double b0 = 1, double b1 = 1, double b2 = 1, double a0 = 1, double a1 = 1, double a2 = 1, uint32_t channels = 2)
            {
                m_id = id;
                config = ma_biquad_config_init(ma_format_s16, 2, b0, b1, b2, a0, a1, a2);
                return ma_biquad_init(&config, &filter);
            }

            int refresh()
            {
                return ma_biquad_init(&config, &filter);
            }

            int process(const void *input, size_t inputSize, void *output) override
            {
                if(isActive)
                {
                    return ma_biquad_process_pcm_frames(&filter, output, input, inputSize);
                }
                return 0;
            }

            const std::string &getId() const override
            {
                return m_id;
            }

            const esnd::FilterType getFilterType() const override
            {
                return esnd::FilterType::Biquad;
            }

            ma_biquad_config config;
            ma_biquad filter;

        private:
            std::string m_id = "default_biquad_id";
    };
}

#endif //EMUSOUND_BIQUADFILTER_HPP
