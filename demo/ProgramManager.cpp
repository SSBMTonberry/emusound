//
// Created by robin on 28.03.2020.
//

#include <audio/filters/BiquadFilter.hpp>
#include "ProgramManager.h"

esnddemo::ProgramManager::ProgramManager(const std::string &title, const sf::Vector2i &windowSize, const sf::Vector2i &resolution, int style,
                                          const sf::ContextSettings &settings)
{
    m_window.create(sf::VideoMode(windowSize.x, windowSize.y), title, style, settings);
    m_window.setView(sf::View(sf::FloatRect(0.f, 0.f, resolution.x, resolution.y)));
    m_window.setFramerateLimit(60);

    //m_eventManager.initialize(&m_window); //std::make_unique<pme::EventManager>(m_window.get());
}

bool esnddemo::ProgramManager::initialize()
{
    initializeMusicStream();
    initializeEmuStream();
    initializeAudioManager();
    initializeImGui();
    return true;
}

void esnddemo::ProgramManager::initializeMusicStream()
{
    std::string wavPath =  "./../../content/juhani_junkala/level1.wav";
    std::string oggPath =   "./../../content/juhani_junkala/level2.ogg";
    std::string mp3Path =   "./../../content/juhani_junkala/level3.mp3";
    std::string flacPath =   "./../../content/juhani_junkala/ending.flac";

    auto wav = std::make_unique<esnd::MusicStream>("WAV ", wavPath);
    auto ogg = std::make_unique<esnd::MusicStream>("OGG ", oggPath);
    auto mp3 = std::make_unique<esnd::MusicStream>("MP3 ", mp3Path);
    auto flac = std::make_unique<esnd::MusicStream>("FLAC", flacPath);

    if(wav->getLoadStatus() == esnd::StreamLoadStatus::OK)
        m_musicStreams.emplace_back(std::move(wav));
    else
        wav->onShutdown();

    if(ogg->getLoadStatus() == esnd::StreamLoadStatus::OK)
        m_musicStreams.emplace_back(std::move(ogg));
    else
        ogg->onShutdown();

    if(mp3->getLoadStatus() == esnd::StreamLoadStatus::OK)
        m_musicStreams.emplace_back(std::move(mp3));
    else
        mp3->onShutdown();

    if(flac->getLoadStatus() == esnd::StreamLoadStatus::OK)
        m_musicStreams.emplace_back(std::move(flac));
    else
        flac->onShutdown();

    for(auto &stream : m_musicStreams)
    {
        stream->addFilter<esnd::BiquadFilter>(    "Biquad:     ")->isActive = false;
        stream->addFilter<esnd::LowpassFilter1>(  "Lowpass 1:  ", 200)->isActive = false;
        stream->addFilter<esnd::LowpassFilter2>(  "Lowpass 2:  ", 200, 1)->isActive = false;
        stream->addFilter<esnd::HighpassFilter1>( "Highpass 1: ", 1000)->isActive = false;
        stream->addFilter<esnd::HighpassFilter2>( "Highpass 2: ", 1000, 1)->isActive = false;
        stream->addFilter<esnd::BandpassFilter>(  "Bandpass:   ", 200, 1)->isActive = false;
        stream->addFilter<esnd::PeakingEqFilter>( "Peaking EQ: ", 1, 1, 1000)->isActive = false;
        stream->addFilter<esnd::NotchingFilter>(  "Notching:   ", 1, 1000)->isActive = false;
        stream->addFilter<esnd::LowshelfFilter>(  "Lowshelf:   ", 5, 1, 1000)->isActive = false;
        stream->addFilter<esnd::HighshelfFilter>( "Highshelf:  ", 5, 1, 1000)->isActive = false;
    }


}

void esnddemo::ProgramManager::initializeEmuStream()
{
    std::string nsfePath =  "./../../content/emu_tests/blueshadow.nsfe";
    //std::string nsfPath =   "./../../content/emu_tests/test.nsf";
    std::string spcPath =   "./../../content/emu_tests/test.spc";
    std::string vgmPath =   "./../../content/emu_tests/test.vgm";

    auto nsfe = std::make_unique<esnd::EmuStream>("NSFE", nsfePath);
    auto nsf = std::make_unique<esnd::EmuStream>("NSF ", (void *)file::_TEST_2_NSF, file::_TEST_2_NSF_SIZE);
    auto spc = std::make_unique<esnd::EmuStream>("SPC ", spcPath);
    auto vgm = std::make_unique<esnd::EmuStream>("VGM ", vgmPath);
    if(nsfe->getLoadStatus() == esnd::StreamLoadStatus::OK)
        m_streams.emplace_back(std::move(nsfe));
    else
        nsfe->onShutdown();

    if(nsf->getLoadStatus() == esnd::StreamLoadStatus::OK)
        m_streams.emplace_back(std::move(nsf));
    else
        nsf->onShutdown();

    if(spc->getLoadStatus() == esnd::StreamLoadStatus::OK)
        m_streams.emplace_back(std::move(spc));
    else
        spc->onShutdown();

    if(vgm->getLoadStatus() == esnd::StreamLoadStatus::OK)
        m_streams.emplace_back(std::move(vgm));
    else
        vgm->onShutdown();

    for(auto &stream : m_streams)
    {
        stream->addFilter<esnd::BiquadFilter>(    "Biquad:     ")->isActive = false;
        stream->addFilter<esnd::LowpassFilter1>(  "Lowpass 1:  ", 200)->isActive = false;
        stream->addFilter<esnd::LowpassFilter2>(  "Lowpass 2:  ", 200, 1)->isActive = false;
        stream->addFilter<esnd::HighpassFilter1>( "Highpass 1: ", 1000)->isActive = false;
        stream->addFilter<esnd::HighpassFilter2>( "Highpass 2: ", 1000, 1)->isActive = false;
        stream->addFilter<esnd::BandpassFilter>(  "Bandpass:   ", 200, 1)->isActive = false;
        stream->addFilter<esnd::PeakingEqFilter>( "Peaking EQ: ", 1, 1, 1000)->isActive = false;
        stream->addFilter<esnd::NotchingFilter>(  "Notching:   ", 1, 1000)->isActive = false;
        stream->addFilter<esnd::LowshelfFilter>(  "Lowshelf:   ", 5, 1, 1000)->isActive = false;
        stream->addFilter<esnd::HighshelfFilter>( "Highshelf:  ", 5, 1, 1000)->isActive = false;
    }

    m_waveforms.emplace_back(std::make_unique<esnd::Waveform>("Square:   ",0.2, 1000, esnd::WaveformType::Square));
    m_waveforms.emplace_back(std::make_unique<esnd::Waveform>("Sine:     ",0.2, 1000, esnd::WaveformType::Sine));
    m_waveforms.emplace_back(std::make_unique<esnd::Waveform>("Triangle: ",0.2, 1000, esnd::WaveformType::Triangle));
    m_waveforms.emplace_back(std::make_unique<esnd::Waveform>("Sawtooth: ",0.2, 1000, esnd::WaveformType::Sawtooth));

    m_noises.emplace_back(std::make_unique<esnd::Noise>("White:   ",1, 1.0, esnd::NoiseType::White));
    m_noises.emplace_back(std::make_unique<esnd::Noise>("Pink:     ",1, 1.0, esnd::NoiseType::Pink));
    m_noises.emplace_back(std::make_unique<esnd::Noise>("Brownian: ",1, 1.0, esnd::NoiseType::Brownian));

    //Waveforms are a bit loud, so set the volume to 50%
    for(auto &waveform : m_waveforms)
        waveform->setVolume(0.50f);

    //Noises are noisy, so adjust the volume a BIT down.
    for(auto &noise : m_noises)
        noise->setVolume(0.15f);
}

void esnddemo::ProgramManager::initializeAudioManager()
{

}

void esnddemo::ProgramManager::initializeImGui()
{
    //ImGui init
    ImGui::CreateContext(); //IMGUI 1.60
    m_style = &ImGui::GetStyle();
    m_io = &ImGui::GetIO();
    m_io->IniFilename = nullptr; //Remove .ini-file

    ImGui::SFML::Init(m_window);
    //Enable Ctrl+TAB (New in ImGui 1.63)
    //m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; //Disabled due to interrupting hotkeys...
    m_io->ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
    m_io->ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;
    //Enable docking
    m_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    //Colors
    ImGui::StyleColorsDark();

    m_io->FontGlobalScale = 1.f;
}

bool esnddemo::ProgramManager::run()
{
    bool quit = false;
    sf::Clock clock;

    while(m_window.isOpen() && !quit)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            quit = true;

        update(clock.getElapsedTime());
        draw();
    }

    shutdown();

    return true;
}

void esnddemo::ProgramManager::update(const sf::Time &time)
{
    m_events.clear();
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        m_events.push_back(event);
    }

    for(auto const & event : m_events)
        ImGui::SFML::ProcessEvent(event);

    ImGui::SFML::Update(m_window, m_deltaClock.restart());
}

void esnddemo::ProgramManager::draw()
{
    m_window.clear(sf::Color(100, 149, 237, 255));
    drawForms();
    ImGui::SFML::Render(m_window);
    m_window.display();
}

void esnddemo::ProgramManager::drawForms()
{
    drawMusicStreamForm();
    drawEmuStreamForm();
    drawAudioManagerForm();
    drawFilterForm();
    drawWaveformForm();
    drawNoiseForm();
    drawWaveformPianoForm();
}

void esnddemo::ProgramManager::drawMusicStreamForm()
{
    static bool first = true;
    if(first)
    {
        ImGui::SetNextWindowPos({0.f, (float) m_window.getSize().y * 0.50f});
        ImGui::SetNextWindowSize({(float) m_window.getSize().x * 0.34f, (float) m_window.getSize().y * 0.25f});
        first = false;
    }
    ImGui::Begin("Music");
    for(auto &stream : m_musicStreams)
    {
        ImGui::Text(stream->getId().c_str()); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Play###Play{0}", stream->getId()).c_str())) stream->play(); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Stop###Stop{0}", stream->getId()).c_str())) stream->stop(); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Filter###Filter{0}", stream->getId()).c_str())) m_streamForFilter = stream.get(); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Seek###Seek{0}", stream->getId()).c_str())) stream->seek(m_seek); ImGui::SameLine();

        ImGui::PushItemWidth(100);
        ImGui::DragFloat(fmt::format("Volume###Volume{0}", stream->getId()).c_str(),
                         stream->getVolumePtr(), 0.05f, 0.0f, 1.5f);
        ImGui::PopItemWidth();
    }
    ImGui::PushItemWidth(100);
    if(ImGui::InputInt("Seek value(ms)###seek_music", &m_seek, 1000, 500))
    {
        if(m_seek < 0) m_seek = 0;
    }
    ImGui::PopItemWidth();
    ImGui::NewLine();
    if(ImGui::Button("STOP!###stop_music", {100, 40}))
    {
        for(auto &stream : m_musicStreams)
            stream->stop();
    }


    ImGui::End();
}

void esnddemo::ProgramManager::drawEmuStreamForm()
{
    static bool first = true;
    if(first)
    {
        ImGui::SetNextWindowPos({0.f, (float) m_window.getSize().y * 0.25f});
        ImGui::SetNextWindowSize({(float) m_window.getSize().x * 0.34f, (float) m_window.getSize().y * 0.25f});
        first = false;
    }
    ImGui::Begin("Emu music");
    for(auto &stream : m_streams)
    {
        esnd::EmuStream *emuStream = dynamic_cast<esnd::EmuStream*>(stream.get());
        ImGui::Text(emuStream->getId().c_str()); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Play###Play{0}", emuStream->getId()).c_str())) emuStream->play(); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Stop###Stop{0}", emuStream->getId()).c_str())) emuStream->stop(); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("<-###<-{0}", emuStream->getId()).c_str())) emuStream->previousTrack(); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("->###->{0}", emuStream->getId()).c_str())) emuStream->nextTrack(); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Filter###Filter{0}", emuStream->getId()).c_str())) m_streamForFilter = emuStream; ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Seek###Seek{0}", emuStream->getId()).c_str())) emuStream->seek(m_seek); ImGui::SameLine();

        ImGui::PushItemWidth(100);
        ImGui::DragFloat(fmt::format("Volume###Volume{0}", emuStream->getId()).c_str(),
                emuStream->getVolumePtr(), 0.05f, 0.0f, 1.5f);
        ImGui::PopItemWidth();
    }
    ImGui::PushItemWidth(100);
    if(ImGui::InputInt("Seek value(ms)", &m_seek, 1000, 500))
    {
        if(m_seek < 0) m_seek = 0;
    }
    ImGui::PopItemWidth();
    ImGui::NewLine();
    if(ImGui::Button("STOP!", {100, 40}))
    {
        for(auto &stream : m_streams)
            stream->stop();
    }


    ImGui::End();
}

void esnddemo::ProgramManager::drawAudioManagerForm()
{

}

void esnddemo::ProgramManager::drawWaveformPianoForm()
{
    static bool first = true;
    if(first)
    {
        ImGui::SetNextWindowPos({(float) m_window.getSize().x * 0.66f, 0});
        ImGui::SetNextWindowSize({(float) m_window.getSize().x * 0.34f, (float) m_window.getSize().y * 0.25f});
        first = false;
    }
    ImGui::Begin("Waveform piano");
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        m_playPiano = false;
    }

    auto notes = m_notes.range(esnd::Note::A0, esnd::Note::G7Sharp);

    if(m_pianoWaveform != nullptr)
    {
        for(int i = 0; i < notes.size(); ++i)
        {
            bool newLine = (i > 0 && (i % 12) == 0);
            if(newLine)
                ImGui::NewLine();

            drawWaveformPianoPart(notes[i].first, notes[i].second);

        }
    }
    ImGui::End();
}

void esnddemo::ProgramManager::drawWaveformPianoPart(const std::string &id, double frequency)
{
    ma_waveform_config *conf = &m_pianoWaveform->getConfig()->config;
    if(ImGui::SmallButton(fmt::format("{1}###{1}{0}", m_pianoWaveform->getId(), id).c_str()))
    {
        conf->frequency = frequency;
        m_pianoWaveform->refresh();
        m_playPiano = true;
    }
    ImGui::SameLine();
}

void esnddemo::ProgramManager::drawWaveformForm()
{
    static bool first = true;
    if(first)
    {
        ImGui::SetNextWindowPos({0, 0});
        ImGui::SetNextWindowSize({(float) m_window.getSize().x * 0.66f, (float) m_window.getSize().y * 0.25f});
        first = false;
    }
    ImGui::Begin("Waveforms");
    for(auto &waveform : m_waveforms)
    {
        double min_amp = 0.2, min_freq = 10;
        double max_amp = 100.0, max_freq = 5000;
        ImGui::Text(waveform->getId().c_str());
        ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Play###Playwave{0}", waveform->getId()).c_str())) waveform->play(); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Stop###Stopwave{0}", waveform->getId()).c_str())) waveform->stop(); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Send to piano###ToPiano{0}", waveform->getId()).c_str())) m_pianoWaveform = waveform.get(); ImGui::SameLine();
        ImGui::PushItemWidth(100);
        if(ImGui::SliderScalarN(fmt::format("amplitude###amplitudewave{0}", waveform->getId()).c_str(), ImGuiDataType_Double,
                &waveform->getConfig()->config.amplitude, 1, &min_amp, &max_amp))
        {
            waveform->refresh();
        }
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PushItemWidth(250);
        if(ImGui::SliderScalarN(fmt::format("frequency###frequencywave{0}", waveform->getId()).c_str(), ImGuiDataType_Double,
                &waveform->getConfig()->config.frequency, 1, &min_freq, &max_freq))
        {
            waveform->refresh();
        }
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PushItemWidth(100);
        ImGui::DragFloat(fmt::format("Volume###Volume{0}", waveform->getId()).c_str(),
                         waveform->getVolumePtr(), 0.05f, 0.0f, 1.5f);
        ImGui::PopItemWidth();
    }

    if(ImGui::Button("STOP!", {100, 40}))
    {
        for(auto &waveform : m_waveforms)
            waveform->stop();
    }
    ImGui::End();
}

void esnddemo::ProgramManager::drawNoiseForm()
{
    static bool first = true;
    if(first)
    {
        ImGui::SetNextWindowPos({0, (float) m_window.getSize().y * 0.75f});
        ImGui::SetNextWindowSize({(float) m_window.getSize().x * 0.50f, (float) m_window.getSize().y * 0.15f});
        first = false;
    }
    ImGui::Begin("Noise");
    for(auto &noise : m_noises)
    {
        int min_freq = 0, max_freq = 100;
        double min_amp = 0.2;
        double max_amp = 100.0;
        ImGui::Text(noise->getId().c_str());
        ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Play###Playnoise{0}", noise->getId()).c_str())) noise->play(); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Stop###Stopnoise{0}", noise->getId()).c_str())) noise->stop(); ImGui::SameLine();
        ImGui::PushItemWidth(250);
        if(ImGui::SliderInt(fmt::format("seed###seednoise{0}", noise->getId()).c_str(),
                                &noise->getConfig()->config.seed, min_freq, max_freq))
        {
            noise->refresh();
        }
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PushItemWidth(100);
        if(ImGui::SliderScalarN(fmt::format("amplitude###amplitudenoise{0}", noise->getId()).c_str(), ImGuiDataType_Double,
                                &noise->getConfig()->config.amplitude, 1, &min_amp, &max_amp))
        {
            noise->refresh();
        }
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PushItemWidth(100);
        ImGui::DragFloat(fmt::format("Volume###Volume{0}", noise->getId()).c_str(),
                         noise->getVolumePtr(), 0.05f, 0.0f, 1.5f);
        ImGui::PopItemWidth();
    }

    if(ImGui::Button("STOP!", {100, 40}))
    {
        for(auto &noise : m_noises)
            noise->stop();
    }
    ImGui::End();
}

void esnddemo::ProgramManager::drawFilterForm()
{
    std::string filterid = (m_streamForFilter == nullptr) ? "" : m_streamForFilter->getId();
    std::string imguiId = (m_streamForFilter == nullptr) ? "Filters###Filters" : fmt::format("Filters ({0})###Filters", filterid);

    static bool first = true;
    if(first)
    {
        ImGui::SetNextWindowPos({(float) m_window.getSize().x * 0.34f, (float) m_window.getSize().y * 0.25f});
        ImGui::SetNextWindowSize({(float) m_window.getSize().x * 0.66f, (float) m_window.getSize().y * 0.50f});
        first = false;
    }
    ImGui::Begin(imguiId.c_str());
    if(m_streamForFilter != nullptr)
    {
        for(auto &filter : *m_streamForFilter->getFilters())
        {
            manageFilter(filter.get());
        }
    }
    ImGui::End();
}

void esnddemo::ProgramManager::manageFilter(esnd::ISoundFilter *filter)
{
    ImGui::Text(filter->getId().c_str());
    switch(filter->getFilterType())
    {
        case esnd::FilterType::Biquad:
            handleBiquadFilter(dynamic_cast<esnd::BiquadFilter*>(filter));
            break;

        case esnd::FilterType::LowpassFirstOrder:
            handleLowpassFilter1(dynamic_cast<esnd::LowpassFilter1*>(filter));
            break;

        case esnd::FilterType::LowpassSecondOrder:
            handleLowpassFilter2(dynamic_cast<esnd::LowpassFilter2*>(filter));
            break;

        case esnd::FilterType::HighpassFirstOrder:
            handleHighpassFilter1(dynamic_cast<esnd::HighpassFilter1*>(filter));
            break;

        case esnd::FilterType::HighpassSecondOrder:
            handleHighpassFilter2(dynamic_cast<esnd::HighpassFilter2*>(filter));
            break;

        case esnd::FilterType::BandpassSecondOrder:
            handleBandpassFilter(dynamic_cast<esnd::BandpassFilter*>(filter));
            break;

        case esnd::FilterType::PeakingEqSecondOrder:
            handlePeakingEqFilter(dynamic_cast<esnd::PeakingEqFilter*>(filter));
            break;

        case esnd::FilterType::NotchingSecondOrder:
            handleNotchingFilter(dynamic_cast<esnd::NotchingFilter*>(filter));
            break;

        case esnd::FilterType::LowshelfSecondOrder:
            handleLowshelfFilter(dynamic_cast<esnd::LowshelfFilter*>(filter));
            break;

        case esnd::FilterType::HighshelfSecondOrder:
            handleHighshelfFilter(dynamic_cast<esnd::HighshelfFilter*>(filter));
            break;
    }

}

void esnddemo::ProgramManager::handleBiquadFilter(esnd::BiquadFilter *filter)
{
    double min = 0.01;
    double max = 1000.0;
    double a[3] {filter->config.a0, filter->config.a1, filter->config.a2};
    double b[3] {filter->config.b0, filter->config.b1, filter->config.b2};
    ImGui::SameLine();
    ImGui::PushItemWidth(200);
    if(ImGui::SliderScalarN(fmt::format("a###abiq{0}", filter->getId()).c_str(), ImGuiDataType_Double, &a, 3, &min, &max))
    {
        filter->config.a0 = a[0];
        filter->config.a1 = a[1];
        filter->config.a2 = a[2];
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(200);
    if(ImGui::SliderScalarN(fmt::format("b###bbiq{0}", filter->getId()).c_str(), ImGuiDataType_Double, &b, 3, &min, &max))
    {
        filter->config.b0 = b[0];
        filter->config.b1 = b[1];
        filter->config.b2 = b[2];
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::Checkbox(fmt::format("active###activebiq{0}", filter->getId()).c_str(), &filter->isActive))
    {

    }
    ImGui::PopItemWidth();
}

void esnddemo::ProgramManager::handleLowpassFilter1(esnd::LowpassFilter1 *filter)
{
    double min = 0;
    double max = 1000.0;
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("cutoffFrequency###cutofflpf1{0}", filter->getId()).c_str(), ImGuiDataType_Double, &filter->config.cutoffFrequency, 1, &min, &max))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::Checkbox(fmt::format("active###activelpf1{0}", filter->getId()).c_str(), &filter->isActive))
    {

    }
    ImGui::PopItemWidth();
}

void esnddemo::ProgramManager::handleLowpassFilter2(esnd::LowpassFilter2 *filter)
{
    double min = 0, min_q = 0;
    double max = 1000.0, max_q = 2;
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("cutoffFrequency###cutofflpf2{0}", filter->getId()).c_str(), ImGuiDataType_Double, &filter->config.cutoffFrequency, 1, &min, &max))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("q###qlpf2{0}", filter->getId()).c_str(), ImGuiDataType_Double, &filter->config.q, 1, &min_q, &max_q))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::Checkbox(fmt::format("active###activelpf2{0}", filter->getId()).c_str(), &filter->isActive))
    {

    }
    ImGui::PopItemWidth();
}

void esnddemo::ProgramManager::handleHighpassFilter1(esnd::HighpassFilter1 *filter)
{
    double min = 200;
    double max = 5000.0;
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("cutoffFrequency###cutoffhp1{0}", filter->getId()).c_str(), ImGuiDataType_Double, &filter->config.cutoffFrequency, 1, &min, &max))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::Checkbox(fmt::format("active###activehp1{0}", filter->getId()).c_str(), &filter->isActive))
    {

    }
    ImGui::PopItemWidth();
}

void esnddemo::ProgramManager::handleHighpassFilter2(esnd::HighpassFilter2 *filter)
{
    double min = 200, min_q = 0;
    double max = 5000.0, max_q = 2;
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("cutoffFrequency###cutoffhp2{0}", filter->getId()).c_str(), ImGuiDataType_Double, &filter->config.cutoffFrequency, 1, &min, &max))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("q###qhp2{0}", filter->getId()).c_str(), ImGuiDataType_Double, &filter->config.q, 1, &min_q, &max_q))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::Checkbox(fmt::format("active###activehp2{0}", filter->getId()).c_str(), &filter->isActive))
    {

    }
    ImGui::PopItemWidth();
}

void esnddemo::ProgramManager::handleBandpassFilter(esnd::BandpassFilter *filter)
{
    double min = 50, min_q = 0.01;
    double max = 2500.0, max_q = 2;
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("cutoffFrequency###cutoffbp{0}", filter->getId()).c_str(), ImGuiDataType_Double, &filter->config.cutoffFrequency, 1, &min, &max))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("q###qbp{0}", filter->getId()).c_str(), ImGuiDataType_Double, &filter->config.q, 1, &min_q, &max_q))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::Checkbox(fmt::format("active###activebp{0}", filter->getId()).c_str(), &filter->isActive))
    {

    }
    ImGui::PopItemWidth();
}

void esnddemo::ProgramManager::handlePeakingEqFilter(esnd::PeakingEqFilter *filter)
{
    double minGain = 0.1, min_q = 0.001, min_frequency = 100;
    double maxGain = 20.0, max_q = 5, max_frequency = 5000.0;
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("gain###gainpeakeq{0}", filter->getId()).c_str(), ImGuiDataType_Double,
            &filter->config.gainDB, 1, &minGain, &maxGain))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("q###qpeakeq{0}", filter->getId()).c_str(), ImGuiDataType_Double,
            &filter->config.q, 1, &min_q, &max_q))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("frequency###frequencypeakeq{0}", filter->getId()).c_str(), ImGuiDataType_Double,
            &filter->config.frequency, 1, &min_frequency, &max_frequency))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::Checkbox(fmt::format("active###activepeakeq{0}", filter->getId()).c_str(), &filter->isActive))
    {

    }
    ImGui::PopItemWidth();
}

void esnddemo::ProgramManager::handleNotchingFilter(esnd::NotchingFilter *filter)
{
    double min_q = 0.01, min_frequency = 100;
    double max_q = 5, max_frequency = 5000.0;
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("q###qnotching{0}", filter->getId()).c_str(), ImGuiDataType_Double,
                            &filter->config.q, 1, &min_q, &max_q))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("frequency###frequencynotching{0}", filter->getId()).c_str(), ImGuiDataType_Double,
                            &filter->config.frequency, 1, &min_frequency, &max_frequency))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::Checkbox(fmt::format("active###activenotching{0}", filter->getId()).c_str(), &filter->isActive))
    {

    }
    ImGui::PopItemWidth();
}

void esnddemo::ProgramManager::handleLowshelfFilter(esnd::LowshelfFilter *filter)
{
    double minGain = 0.1, min_shelfSlope = 0.1, min_frequency = 100;
    double maxGain = 10.0, max_shelfSlope = 6.5, max_frequency = 5000.0;
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("gain###gainlowshelf{0}", filter->getId()).c_str(), ImGuiDataType_Double,
                            &filter->config.gainDB, 1, &minGain, &maxGain))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("shelfSlope###shelfSlopelowshelf{0}", filter->getId()).c_str(), ImGuiDataType_Double,
                            &filter->config.shelfSlope, 1, &min_shelfSlope, &max_shelfSlope))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("frequency###frequencylowshelf{0}", filter->getId()).c_str(), ImGuiDataType_Double,
                            &filter->config.frequency, 1, &min_frequency, &max_frequency))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::Checkbox(fmt::format("active###activelowshelf{0}", filter->getId()).c_str(), &filter->isActive))
    {

    }
    ImGui::PopItemWidth();
}

void esnddemo::ProgramManager::handleHighshelfFilter(esnd::HighshelfFilter *filter)
{
    double minGain = 0.1, min_shelfSlope = 0.1, min_frequency = 100;
    double maxGain = 10.0, max_shelfSlope = 6.5, max_frequency = 5000.0;
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("gain###gainhighshelf{0}", filter->getId()).c_str(), ImGuiDataType_Double,
                            &filter->config.gainDB, 1, &minGain, &maxGain))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("shelfSlope###shelfSlopehighshelf{0}", filter->getId()).c_str(), ImGuiDataType_Double,
                            &filter->config.shelfSlope, 1, &min_shelfSlope, &max_shelfSlope))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::SliderScalarN(fmt::format("frequency###frequencyhighshelf{0}", filter->getId()).c_str(), ImGuiDataType_Double,
                            &filter->config.frequency, 1, &min_frequency, &max_frequency))
    {
        filter->refresh();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::Checkbox(fmt::format("active###activehighshelf{0}", filter->getId()).c_str(), &filter->isActive))
    {

    }
    ImGui::PopItemWidth();
}

void esnddemo::ProgramManager::shutdown()
{
    for(auto &stream : m_streams)
        stream->onShutdown();

    for(auto &stream : m_musicStreams)
        stream->onShutdown();

    for(auto &waveform : m_waveforms)
        waveform->onShutdown();
}


