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

            const std::map<esnd::Note, double> &getNotes() const
            {
                return m_notes;
            }

            const std::map<esnd::Note, std::string> &getNoteNames() const
            {
                return m_noteNames;
            }

            double get(esnd::Note note)
            {
                return m_notes[note];
            }

            double get(int note)
            {
                if(note < 0) note = 0;
                else if (note >= m_notes.size()) note = m_notes.size() - 1;
                return m_notes[(esnd::Note) note];
            }

            std::string name(esnd::Note note)
            {
                return m_noteNames[note];
            }

            std::string name(int note)
            {
                if(note < 0) note = 0;
                else if (note >= m_noteNames.size()) note = m_noteNames.size() - 1;
                return m_noteNames[(esnd::Note) note];
            }

            std::vector<std::pair<std::string, double>> range(int fromNote, int toNote)
            {
                std::vector<std::pair<std::string, double>> range;
                for(int i = fromNote; i <= toNote; ++i)
                    range.emplace_back(name(i), get(i));

                return range;
            }

            std::vector<std::pair<std::string, double>> range(esnd::Note fromNote, esnd::Note toNote)
            {
                std::vector<std::pair<std::string, double>> range;
                int to = (int)toNote;
                for(int i = (int)fromNote; i <= to; ++i)
                    range.emplace_back(name(i), get(i));

                return range;
            }

        private:
            std::map<esnd::Note, double> getAllNotes()
            {
                m_notes.clear();
                std::string notes[12] = { "A", "A# ", "B", "C", "C# ", "D", "D# ", "E", "F", "F# ", "G", "G# "};

                double ratio = pow(2.0, 1.0/12.0);

                double a = 27.500;
                int octaves = 8;
                int totalNotes = 12 * octaves;

                for (int i=0; i < totalNotes; i++)
                {
                    std::stringstream notename;
                    double value = a * pow(ratio, i);
                    int octave = i/12;
                    notename << notes[i%12] << octave;

                    m_notes[(esnd::Note)i] = value;
                    m_noteNames[(esnd::Note)i] = notename.str();
                }

                return m_notes;
            }

            std::map<esnd::Note, double> m_notes;
            std::map<esnd::Note, std::string> m_noteNames;
    };

}

#endif //EMUSOUND_NOTES_HPP
