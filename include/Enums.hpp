//
// Created by robin on 25.03.2020.
//

#ifndef EMUSOUND_ENUMS_HPP
#define EMUSOUND_ENUMS_HPP

#include "external/emusound_external.h"

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
     * 200 - 299 = Waveform related
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
        EmuErrorLoadingTrackData = 106,

        WaveformInitError = 200,
        WaveformDeviceError = 201,
        WaveformStartupFailure = 202
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

    enum class WaveformType
    {
        Sine = ma_waveform_type_sine,
        Square = ma_waveform_type_square,
        Triangle = ma_waveform_type_triangle,
        Sawtooth = ma_waveform_type_sawtooth
    };

    enum class Note : uint8_t
    {
            A0 =        0,
            A0Sharp =   1,
            B0 =        2,
            C0 =        3,
            C0Sharp =   4,
            D0 =        5,
            D0Sharp =   6,
            E0 =        7,
            F0 =        8,
            F0Sharp =   9,
            G0 =       10,
            G0Sharp =  11,

            A1 =       12,
            A1Sharp =  13,
            B1 =       14,
            C1 =       15,
            C1Sharp =  16,
            D1 =       17,
            D1Sharp =  18,
            E1 =       19,
            F1 =       20,
            F1Sharp =  21,
            G1 =       22,
            G1Sharp =  23,

            A2 =       24,
            A2Sharp =  25,
            B2 =       26,
            C2 =       27,
            C2Sharp =  28,
            D2 =       29,
            D2Sharp =  30,
            E2 =       31,
            F2 =       32,
            F2Sharp =  33,
            G2 =       34,
            G2Sharp =  35,

            A3 =       36,
            A3Sharp =  37,
            B3 =       38,
            C3 =       39,
            C3Sharp =  40,
            D3 =       41,
            D3Sharp =  42,
            E3 =       43,
            F3 =       44,
            F3Sharp =  45,
            G3 =       46,
            G3Sharp =  47,

            A4 =       48,
            A4Sharp =  49,
            B4 =       50,
            C4 =       51,
            C4Sharp =  52,
            D4 =       53,
            D4Sharp =  54,
            E4 =       55,
            F4 =       56,
            F4Sharp =  57,
            G4 =       58,
            G4Sharp =  59,

            A5 =       60,
            A5Sharp =  61,
            B5 =       62,
            C5 =       63,
            C5Sharp =  64,
            D5 =       65,
            D5Sharp =  66,
            E5 =       67,
            F5 =       68,
            F5Sharp =  69,
            G5 =       70,
            G5Sharp =  71,

            A6 =       72,
            A6Sharp =  73,
            B6 =       74,
            C6 =       75,
            C6Sharp =  76,
            D6 =       77,
            D6Sharp =  78,
            E6 =       79,
            F6 =       80,
            F6Sharp =  81,
            G6 =       82,
            G6Sharp =  83,

            A7 =       84,
            A7Sharp =  85,
            B7 =       86,
            C7 =       87,
            C7Sharp =  88,
            D7 =       89,
            D7Sharp =  90,
            E7 =       91,
            F7 =       92,
            F7Sharp =  93,
            G7 =       94,
            G7Sharp =  95
    };
}

#endif //EMUSOUND_ENUMS_HPP
