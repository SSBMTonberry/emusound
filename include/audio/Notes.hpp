//
// Created by robin on 30.03.2020.
//

#ifndef EMUSOUND_NOTES_HPP
#define EMUSOUND_NOTES_HPP
namespace esnd
{
    class Notes
    {
        public:
            Notes() = delete;

            //Notes
            static constexpr double A0 =         27.500;
            static constexpr double A0_SHARP =   29.135;
            static constexpr double B0 =         30.863;
            static constexpr double C0 =         32.703;
            static constexpr double C0_SHARP =   34.648;
            static constexpr double D0 =         36.708;
            static constexpr double D0_SHARP =   38.891;
            static constexpr double E0 =         41.203;
            static constexpr double F0 =         43.654;
            static constexpr double F0_SHARP =   46.249;
            static constexpr double G0 =         48.999;
            static constexpr double G0_SHARP =   51.913;

            static constexpr double A1 =         55.000;
            static constexpr double A1_SHARP =   58.270;
            static constexpr double B1 =         61.735;
            static constexpr double C1 =         65.406;
            static constexpr double C1_SHARP =   69.269;
            static constexpr double D1 =         73.461;
            static constexpr double D1_SHARP =   77.782;
            static constexpr double E1 =         82.403;
            static constexpr double F1 =         87.307;
            static constexpr double F1_SHARP =   92.499;
            static constexpr double G1 =         97.999;
            static constexpr double G1_SHARP =  103.830;

            static constexpr double A2 =        110.000;
            static constexpr double A2_SHARP =  116.540;
            static constexpr double B2 =        123.470;
            static constexpr double C2 =        130.810;
            static constexpr double C2_SHARP =  138.590;
            static constexpr double D2 =        146.830;
            static constexpr double D2_SHARP =  155.560;
            static constexpr double E2 =        164.810;
            static constexpr double F2 =        174.610;
            static constexpr double F2_SHARP =  185.000;
            static constexpr double G2 =        196.000;
            static constexpr double G2_SHARP =  207.650;

            static constexpr double A3 =        220.000;
            static constexpr double A3_SHARP =  233.080;
            static constexpr double B3 =        246.940;
            static constexpr double C3 =        261.630;
            static constexpr double C3_SHARP =  277.180;
            static constexpr double D3 =        293.660;
            static constexpr double D3_SHARP =  311.130;
            static constexpr double E3 =        329.630;
            static constexpr double F3 =        349.230;
            static constexpr double F3_SHARP =  369.990;
            static constexpr double G3 =        392.000;
            static constexpr double G3_SHARP =  415.300;

            static constexpr double A4 =        440.000;
            static constexpr double A4_SHARP =  466.160;
            static constexpr double B4 =        493.880;
            static constexpr double C4 =        523.250;
            static constexpr double C4_SHARP =  554.370;
            static constexpr double D4 =        587.330;
            static constexpr double D4_SHARP =  622.250;
            static constexpr double E4 =        659.260;
            static constexpr double F4 =        698.460;
            static constexpr double F4_SHARP =  739.990;
            static constexpr double G4 =        783.990;
            static constexpr double G4_SHARP =  830.610;
    };

}

#endif //EMUSOUND_NOTES_HPP
