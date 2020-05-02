//
// Created by robin on 29.03.2020.
//

#ifndef EMUSOUND_LOWSHELFFILTER_HPP
#define EMUSOUND_LOWSHELFFILTER_HPP

#include "ISoundFilter.h"

namespace esnd
{
    class LowshelfFilter : public ISoundFilter
    {
        public:
            LowshelfFilter() = default;
            LowshelfFilter(const std::string &id, double gainDb, double shelfSlope, double frequency, uint32_t channels = 2, uint32_t sampleRate = 44100)
            {
                init(id, gainDb, shelfSlope, frequency, channels, sampleRate);
            }

            int init(const std::string &id, double gainDb, double shelfSlope, double frequency, uint32_t channels = 2, uint32_t sampleRate = 44100)
            {
                m_id = id;
                config = ma_loshelf2_config_init(ma_format_s16, channels, sampleRate, gainDb, shelfSlope, frequency);
                return ma_loshelf2_init(&config, &filter);
            }

            int refresh()
            {
                return ma_loshelf2_init(&config, &filter);
            }

            int process(const void *input, size_t inputSize, void *output) override
            {
                if(isActive)
                {
                    return ma_loshelf2_process_pcm_frames(&filter, output, input, inputSize);
                }
                return 0;
            }

            const std::string &getId() const override
            {
                return m_id;
            }

            const FilterType getFilterType() const override
            {
                return FilterType::LowshelfSecondOrder;
            }

            ma_loshelf2_config config;
            ma_loshelf2 filter;

        private:
            std::string m_id = "default_lowshelf_id";
    };
}

#endif //EMUSOUND_LOWSHELFFILTER_HPP
