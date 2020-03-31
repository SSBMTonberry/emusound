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
            Notes()
            {
                getAllNotes();
            }

            

        private:
            std::map<esnd::Note, double> getAllNotes()
            {
                m_notes.clear();
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

                    m_notes[(esnd::Note)i] = value; //notename.str();
                    //cout << left << setw(3) << notes[i] << right << a * pow(ratio, i) << endl;
                }

                return m_notes;
            }

            std::map<esnd::Note, double> m_notes;
    };

}

#endif //EMUSOUND_NOTES_HPP
