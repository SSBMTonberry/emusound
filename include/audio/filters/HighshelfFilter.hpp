//
// Created by robin on 29.03.2020.
//

#ifndef EMUSOUND_HIGHSHELFFILTER_HPP
#define EMUSOUND_HIGHSHELFFILTER_HPP

#include "ISoundFilter.h"

namespace esnd
{
    class HighshelfFilter : public ISoundFilter
    {
        public:
            HighshelfFilter() = default;
            HighshelfFilter(ma_decoder *decoder, const std::string &id, double gainDb, double shelfSlope, double frequency, uint32_t channels = 2, uint32_t sampleRate = 44100)
            {
                init(decoder, id, gainDb, shelfSlope, frequency, channels, sampleRate);
            }

            int init(ma_decoder *decoder, const std::string &id, double gainDb, double shelfSlope, double frequency, uint32_t channels = 2, uint32_t sampleRate = 44100)
            {
                m_decoder = decoder;
                m_id = id;
                config = ma_hishelf2_config_init(m_decoder->outputFormat, channels, sampleRate, gainDb, shelfSlope, frequency);
                return ma_hishelf2_init(&config, &filter);
            }

            int refresh()
            {
                return ma_hishelf2_init(&config, &filter);
            }

            int process(const void *input, size_t inputSize, void *output) override
            {
                if(isActive)
                {
                    return ma_hishelf2_process_pcm_frames(&filter, output, input, inputSize);
                }
                return 0;
            }

            const std::string &getId() const override
            {
                return m_id;
            }

            const FilterType getFilterType() const override
            {
                return FilterType::HighshelfSecondOrder;
            }

            ma_hishelf2_config config;
            ma_hishelf2 filter;

        private:
            std::string m_id = "default_lowshelf_id";
    };
}

#endif //EMUSOUND_HIGHSHELFFILTER_HPP
