//
// Created by robin on 30.03.2020.
//

#ifndef EMUSOUND_NOTES_HPP
#define EMUSOUND_NOTES_HPP

#include <sstream>
#include "Enums.hpp"
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

            static constexpr double A5 =        880.000;
            static constexpr double A5_SHARP =  932.330;
            static constexpr double B5 =        987.770;
            static constexpr double C5 =       1046.500;
            static constexpr double C5_SHARP = 1108.700;
            static constexpr double D5 =       1174.700;
            static constexpr double D5_SHARP = 1244.500;
            static constexpr double E5 =       1318.500;
            static constexpr double F5 =       1396.900;
            static constexpr double F5_SHARP = 1480.000;
            static constexpr double G5 =       1568.200;
            static constexpr double G5_SHARP = 1661.200;

            static constexpr double A6 =       1760.000;
            static constexpr double A6_SHARP = 1864.700;
            static constexpr double B6 =       1975.500;
            static constexpr double C6 =       2093.000;
            static constexpr double C6_SHARP = 2217.500;
            static constexpr double D6 =       2349.300;
            static constexpr double D6_SHARP = 2489.000;
            static constexpr double E6 =       2637.000;
            static constexpr double F6 =       2793.000;
            static constexpr double F6_SHARP = 2960.000;
            static constexpr double G6 =       3136.000;
            static constexpr double G6_SHARP = 3322.400;

            static constexpr double A7 =       3520.000;
            static constexpr double A7_SHARP = 3729.300;
            static constexpr double B7 =       3951.100;
            static constexpr double C7 =       4186.000;

            static std::map<double, std::string> getAllNotes()
            {
                std::map<double, std::string> map;

                std::string notes[12] = { "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};

                double ratio = pow(2.0, 1.0/12.0);
                //cout << fixed;
                //cout << setprecision(12);
                //cout << "ratio: " << ratio << endl << endl;

                double a = 27.500;
                int octaves = 8;
                int totalNotes = 12 * octaves;
                //cout << setprecision(4);
                for (int i=0; i < totalNotes; i++)
                {
                    std::stringstream notename;
                    double value = a * pow(ratio, i);
                    int octave = i/12;
                    notename << notes[i%12] << octave;

                    map[value] = notename.str();
                    //cout << left << setw(3) << notes[i] << right << a * pow(ratio, i) << endl;
                }

                return map;
            }
    };

}

#endif //EMUSOUND_NOTES_HPP
