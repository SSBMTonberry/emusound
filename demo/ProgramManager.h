//
// Created by robin on 28.03.2020.
//

#ifndef EMUSOUND_PROGRAMMANAGER_H
#define EMUSOUND_PROGRAMMANAGER_H

#include <pmgui.h>
#include "SFML/Graphics.hpp"
#include "../include/emusound.h"
#include "audio_demo_files_mapper.h"

namespace file = audio_demo_files_files_mapper;

namespace esnddemo
{
    class ProgramManager
    {
        public:
            ProgramManager(const std::string &title, const sf::Vector2i &windowSize, const sf::Vector2i &resolution, int style = sf::Style::Default,
                           const sf::ContextSettings &settings = sf::ContextSettings());

            bool initialize();
            void initializeEmuStream();
            void initializeAudioManager();

            bool run();
            void update(const sf::Time &time);

            void draw();

            void shutdown();

        private:
            void initializeImGui();

            void drawForms();
            void drawEmuStreamForm();
            void drawFilterForm();
            void drawWaveformForm();
            void drawWaveformPianoForm();
            void drawWaveformPianoPart(const std::string &id, double frequency);
            void drawAudioManagerForm();

            void manageFilter(esnd::ISoundFilter *filter);
            void handleLowpassFilter1(esnd::LowpassFilter1 *filter);
            void handleLowpassFilter2(esnd::LowpassFilter2 *filter);
            void handleBiquadFilter(esnd::BiquadFilter *filter);
            void handleHighpassFilter1(esnd::HighpassFilter1 *filter);
            void handleHighpassFilter2(esnd::HighpassFilter2 *filter);
            void handleBandpassFilter(esnd::BandpassFilter *filter);
            void handlePeakingEqFilter(esnd::PeakingEqFilter *filter);
            void handleNotchingFilter(esnd::NotchingFilter *filter);
            void handleLowshelfFilter(esnd::LowshelfFilter *filter);
            void handleHighshelfFilter(esnd::HighshelfFilter *filter);

            sf::RenderWindow m_window;

            std::vector<std::unique_ptr<esnd::ISoundStream>> m_streams;
            std::vector<std::unique_ptr<esnd::Waveform>> m_waveforms;

            esnd::EmuStream *m_streamForFilter = nullptr;
            esnd::Waveform *m_pianoWaveform = nullptr;
            bool m_playPiano = false;

            //ImGui
            int m_seek = 0;
            ImGuiStyle *m_style = nullptr;
            ImGuiIO *m_io = nullptr;
            sf::Clock m_deltaClock;
            std::vector<sf::Event> m_events;

            esnd::Notes m_notes;

    };
}

#endif //EMUSOUND_PROGRAMMANAGER_H
