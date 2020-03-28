//
// Created by robin on 28.03.2020.
//

#ifndef EMUSOUND_PROGRAMMANAGER_H
#define EMUSOUND_PROGRAMMANAGER_H

#include <pmgui.h>
#include "SFML/Graphics.hpp"
#include "../include/emusound.h"
#include "audio_demo_files_mapper.h"

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

        private:
            void initializeImGui();

            void drawForms();
            void drawEmuStreamForm();
            void drawAudioManagerForm();

            sf::RenderWindow m_window;

            //Audio
            esnd::EmuStream m_nsfeDemo;
            esnd::EmuStream m_nsfDemo;
            esnd::EmuStream m_spcDemo;
            esnd::EmuStream m_vgmDemo;

            //ImGui
            ImGuiStyle *m_style = nullptr;
            ImGuiIO *m_io = nullptr;
            sf::Clock m_deltaClock;
            std::vector<sf::Event> m_events;
    };
}

#endif //EMUSOUND_PROGRAMMANAGER_H
