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
        DecoderInitError = 3,

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

    enum class FilterType
    {
        Undefined = 0,

        Biquad = 1,                     //ma_biquad
        LowpassFirstOrder = 2,          //ma_lpf1
        LowpassSecondOrder = 3,         //ma_lpf2
        LowpassConfigurableOrder = 4,   //ma_lpf
        HighpassFirstOrder = 5,         //ma_hpf1
        HighpassSecondOrder = 6,        //ma_hpf2
        HighpassConfigurableOrder = 7,  //ma_hpf
        BandpassSecondOrder = 8,        //ma_bpf2
        BandpassConfigurableOrder = 9,  //ma_bpf
        PeakingEqSecondOrder = 10,      //ma_peak2
        NotchingSecondOrder = 11,       //ma_notch2
        LowshelfSecondOrder = 12,       //ma_loshelf2
        HighshelfSecondOrder = 13,      //ma_hishelf2

        Custom = 999
    };
}

#endif //EMUSOUND_ENUMS_HPP
