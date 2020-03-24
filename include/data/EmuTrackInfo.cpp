//
// Created by robin on 24.03.2020.
//

#include "EmuTrackInfo.h"

esnd::EmuTrackInfo::EmuTrackInfo()
{

}

esnd::EmuTrackInfo::EmuTrackInfo(Music_Emu *emu, int trackNumber)
{
    load(m_emu, m_trackNumber);
}

bool esnd::EmuTrackInfo::load(Music_Emu *emu, int trackNumber)
{
    m_emu = emu;
    m_trackNumber = trackNumber;

    gme_info_t *info;
    if (handleError(gme_track_info(m_emu, &info, m_trackNumber)))
        return false;

    m_system = info->system;
    m_game = info->game;
    m_author = info->author;
    m_copyright = info->copyright;
    m_comment = info->comment;
    m_dumper = info->dumper;
    m_song = info->song;
    m_length = info->length;
    m_playLength = info->play_length;
    m_introLength = info->intro_length;
    m_loopLength = info->loop_length;
    //m_numberOfTracks = gme_track_count(m_emu);
    m_tempo = 1.f;

    if (m_song.empty())
    {
        std::stringstream ss;
        ss << "Track " << (m_trackNumber + 1);
        m_song = ss.str();
    }

    gme_free_info( info );
    return true;
}

const std::string &esnd::EmuTrackInfo::getSystem() const
{
    return m_system;
}

void esnd::EmuTrackInfo::setSystem(const std::string &system)
{
    m_system = system;
}

const std::string &esnd::EmuTrackInfo::getGame() const
{
    return m_game;
}

void esnd::EmuTrackInfo::setGame(const std::string &game)
{
    m_game = game;
}

const std::string &esnd::EmuTrackInfo::getAuthor() const
{
    return m_author;
}

void esnd::EmuTrackInfo::setAuthor(const std::string &author)
{
    m_author = author;
}

const std::string &esnd::EmuTrackInfo::getCopyright() const
{
    return m_copyright;
}

void esnd::EmuTrackInfo::setCopyright(const std::string &copyright)
{
    m_copyright = copyright;
}

const std::string &esnd::EmuTrackInfo::getComment() const
{
    return m_comment;
}

void esnd::EmuTrackInfo::setComment(const std::string &comment)
{
    m_comment = comment;
}

const std::string &esnd::EmuTrackInfo::getDumper() const
{
    return m_dumper;
}

void esnd::EmuTrackInfo::setDumper(const std::string &dumper)
{
    m_dumper = dumper;
}

int esnd::EmuTrackInfo::getLength() const
{
    return m_length;
}

void esnd::EmuTrackInfo::setLength(int length)
{
    m_length = length;
}

int esnd::EmuTrackInfo::getPlayLength() const
{
    return m_playLength; //(m_tempo != 0) ? m_playLength / m_tempo : m_playLength;
}

void esnd::EmuTrackInfo::setPlayLength(int playLength)
{
    m_playLength = playLength;
}

bool esnd::EmuTrackInfo::handleError(const char *errorText)
{
    if(errorText)
    {
        m_errorText = errorText;
        return true;
    }

    return false;
}

int esnd::EmuTrackInfo::getTrackNumber() const
{
    return m_trackNumber;
}

void esnd::EmuTrackInfo::setTrackNumber(int trackNumber)
{
    m_trackNumber = trackNumber;
}

const std::string &esnd::EmuTrackInfo::getSong() const
{
    return m_song;
}

void esnd::EmuTrackInfo::setSong(const std::string &song)
{
    m_song = song;
}

int esnd::EmuTrackInfo::getIntroLength() const
{
    return m_introLength;
}

void esnd::EmuTrackInfo::setIntroLength(int introLength)
{
    m_introLength = introLength;
}

int esnd::EmuTrackInfo::getLoopLength() const
{
    return m_loopLength;
}

void esnd::EmuTrackInfo::setLoopLength(int loopLength)
{
    m_loopLength = loopLength;
}

//int esnd::EmuTrackInfo::getNumberOfTracks() const
//{
//    return m_numberOfTracks;
//}

float esnd::EmuTrackInfo::getTempo() const
{
    return m_tempo;
}

void esnd::EmuTrackInfo::setTempo(float tempo)
{
    m_tempo = tempo;
}

const std::string &esnd::EmuTrackInfo::getErrorText() const
{
    return m_errorText;
}