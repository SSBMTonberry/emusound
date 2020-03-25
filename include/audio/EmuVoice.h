//
// Created by robin on 25.03.2020.
//

#ifndef EMUSOUND_EMUVOICE_H
#define EMUSOUND_EMUVOICE_H

#include <iostream>
#include <Music_Emu.h>
#include <map>

namespace esnd
{
    class EmuVoice
    {
        public:
            EmuVoice() = default;
            EmuVoice(Music_Emu *emu, int channelNo, const std::string &channelName, bool isMuted); //, sf::Keyboard::Key hotkey = sf::Keyboard::Unknown);

            void toggleMute();

            void setEmu(Music_Emu *emu);
            void setChannelNo(int channelNo);
            void setChannelName(const std::string &channelName);
            void setMuted(bool isMuted);

            [[nodiscard]] Music_Emu *getEmu() const;
            int getChannelNo() const;
            [[nodiscard]] const std::string &getChannelName() const;
            bool isMuted() const;
            bool *getMuted();

        private:
            int m_channelNo = 0;
            std::string m_channelName = "";
            bool m_isMuted = false;
            bool m_hotkeyPressed = false;

            Music_Emu *m_emu = nullptr;
    };
}

#endif //EMUSOUND_EMUVOICE_H
