//
// Created by robin on 25.03.2020.
//

#include "EmuVoice.h"

esnd::EmuVoice::EmuVoice(Music_Emu *emu, int channelNo, const std::string &channelName, bool isMuted)
        : m_emu {emu}, m_channelNo {channelNo}, m_channelName {channelName}, m_isMuted {isMuted}
{

}

void esnd::EmuVoice::toggleMute()
{
    setMuted(!m_isMuted);
}

void esnd::EmuVoice::setEmu(Music_Emu *emu)
{
    m_emu = emu;
}

void esnd::EmuVoice::setChannelNo(int channelNo)
{
    m_channelNo = channelNo;
}

void esnd::EmuVoice::setChannelName(const std::string &channelName)
{
    m_channelName = channelName;
}

void esnd::EmuVoice::setMuted(bool isMuted)
{
    m_isMuted = isMuted;
}

Music_Emu *esnd::EmuVoice::getEmu() const
{
    return m_emu;
}

int esnd::EmuVoice::getChannelNo() const
{
    return m_channelNo;
}

const std::string &esnd::EmuVoice::getChannelName() const
{
    return m_channelName;
}

bool esnd::EmuVoice::isMuted() const
{
    return m_isMuted;
}

bool *esnd::EmuVoice::getMuted()
{
    return &m_isMuted;
}
