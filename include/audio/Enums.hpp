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

    /*!
     * 0 - 99 = General
     * 100 - 199 = Emu related
     */
    enum class StreamLoadStatus
    {
        OK = 0,
        StreamOpenFailure = 1,
        StreamStartFailure = 2,


        EmuFileIdentificationError = 100,
        EmuOutOfMemory = 102,
        EmuFileLoadError = 101,
        EmuMemoryLoadError = 102,
        EmuUnsupportedMusicType = 103,
        EmuInvalidSampleRate = 104,
        EmuInvalidTrack = 105,
        EmuErrorLoadingTrackData = 106
    };

    enum class StreamMode
    {
        File = 0,
        Memory = 1
    };
}

#endif //EMUSOUND_ENUMS_HPP
