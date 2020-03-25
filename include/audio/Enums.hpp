//
// Created by robin on 25.03.2020.
//

#ifndef EMUSOUND_ENUMS_HPP
#define EMUSOUND_ENUMS_HPP

namespace esnd
{
    enum class SoundStatus
    {
        Stopped = 0,
        Paused = 1,
        Playing = 2
    };

    enum class StreamMode
    {
        File = 0,
        Memory = 1
    };
}

#endif //EMUSOUND_ENUMS_HPP
