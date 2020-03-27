//
// Created by robin on 27.03.2020.
//

#ifndef EMUSOUND_ISOUNDFILTER_H
#define EMUSOUND_ISOUNDFILTER_H

#include <cstddef>
#include "../../external/emusound_external.h"
namespace esnd
{
    class ISoundFilter
    {
        public:
            /*!
             *
             * @param input
             * @param inputSize <bufferSize> / <number of channels>
             * @param output
             * @return
             */
            virtual int process(const void *input, size_t inputSize, void *output) = 0;
            //virtual std::string getId() = 0;
            virtual const std::string &getId() const = 0;
            bool isActive = true;
    };
}

#endif //EMUSOUND_ISOUNDFILTER_H
