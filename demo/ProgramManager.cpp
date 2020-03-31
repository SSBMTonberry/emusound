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
    initializeEmuStream();
    initializeAudioManager();
    initializeImGui();
    return true;
}

void esnddemo::ProgramManager::initializeEmuStream()
{
    std::string nsfePath =  "./../../content/emu_tests/blueshadow.nsfe";
    //std::string nsfPath =   "./../../content/emu_tests/test.nsf";
    std::string spcPath =   "./../../content/emu_tests/test.spc";
    std::string vgmPath =   "./../../content/emu_tests/test.vgm";

    m_streams.emplace_back(std::make_unique<esnd::EmuStream>("NSFE", nsfePath));//.operator*().setId("NSFE");
    m_streams.emplace_back(std::make_unique<esnd::EmuStream>("NSF ", (void *)file::_TEST_2_NSF, file::_TEST_2_NSF_SIZE));//.operator*().setId("NSF ");
    m_streams.emplace_back(std::make_unique<esnd::EmuStream>("SPC ", spcPath));//.operator*().setId("SPC ");
    m_streams.emplace_back(std::make_unique<esnd::EmuStream>("VGM ", vgmPath));//.operator*().setId("VGM ");

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
}

void esnddemo::ProgramManager::initializeAudioManager()
{
    //fs::path musicPath =    "./../../content/demo/audio/music.mp3";

    //fs::path buttonSfxPath =  "./../../content/demo/audio/button_sfx.wav";
    //fs::path coinSfxPath =    "./../../content/demo/audio/coin_sfx.wav";
    //fs::path test1NsfPath =   "./../../content/demo/audio/test_1.nsf";

    //AudioManager::get()->addSoundData("music_memory", {file::_MUSIC_OGG, file::_MUSIC_OGG_SIZE}, false);
    //AudioManager::get()->addSoundData("emu_data", {file::_TEST_2_NSF, file::_TEST_2_NSF_SIZE}, false);
    //AudioManager::get()->createMusicFromSoundData("music_memory");
    ////AudioManager::get()->createMusicFromPath("music_path", musicPath); //MP3 is not supported by SFML.
    //AudioManager::get()->addSoundBuffer("button_sfx", buttonSfxPath, true);
    //AudioManager::get()->addSoundBuffer("coin_sfx", coinSfxPath, true);
    //AudioManager::get()->addSoundData("explosion_sfx", {file::_EXPLOSION_SFX_WAV, file::_EXPLOSION_SFX_WAV_SIZE}, true);
    //AudioManager::get()->addSoundData("hit_sfx", {file::_HIT_SFX_WAV, file::_HIT_SFX_WAV_SIZE}, true);
//
    //AudioManager::get()->createEmuStream("nsf_file", test1NsfPath);
    //AudioManager::get()->createEmuStream("nsf_sfx", file::_NSF_SFX_NSFE, file::_NSF_SFX_NSFE_SIZE);
    //AudioManager::get()->createEmuStreamFromSoundData("emu_data");
//
    ////Emu generated SFX
    //AudioManager::get()->addSoundBuffer("emu_sfx_1", AudioManager::get()->getEmuStream("nsf_sfx")->createSoundBufferForTrack(2, 0, 1500), true);
    //AudioManager::get()->addSoundBuffer("emu_sfx_2", AudioManager::get()->getEmuStream("nsf_sfx")->createSoundBufferForTrack(3, 0, 1000), true);
    //AudioManager::get()->addSoundBuffer("emu_sfx_3", AudioManager::get()->getEmuStream("nsf_sfx")->createSoundBufferForTrack(7, 0, 3500), true);
    //AudioManager::get()->addSoundBuffer("emu_sfx_3_quick", AudioManager::get()->getEmuStream("nsf_sfx")->createSoundBufferForTrack(7, 0, 3500, 2.f), true);
}

void esnddemo::ProgramManager::initializeImGui()
{
    //ImGui init
    ImGui::CreateContext(); //IMGUI 1.60
    m_style = &ImGui::GetStyle();
    m_io = &ImGui::GetIO();

    ImGui::SFML::Init(m_window);
    //Enable Ctrl+TAB (New in ImGui 1.63)
    //m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; //Removed - 18.03.2019 - Disabled due to interrupting hotkeys...
    m_io->ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
    m_io->ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;
    //Enable docking (New in ImGui 1.66 WIP) - Downloaded 14.10.2018
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
    drawEmuStreamForm();
    drawAudioManagerForm();
    drawFilterForm();
    drawWaveformForm();
    drawWaveformPianoForm();
}

void esnddemo::ProgramManager::drawEmuStreamForm()
{
    ImGui::Begin("Audio");
    for(auto &stream : m_streams)
    {
        esnd::EmuStream *emuStream = dynamic_cast<esnd::EmuStream*>(stream.get());
        ImGui::Text(emuStream->getId().c_str()); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Play###Play{0}", emuStream->getId()).c_str())) emuStream->play(); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Stop###Stop{0}", emuStream->getId()).c_str())) emuStream->stop(); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("<-###<-{0}", emuStream->getId()).c_str())) emuStream->previousTrack(); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("->###->{0}", emuStream->getId()).c_str())) emuStream->nextTrack(); ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Filter###Filter{0}", emuStream->getId()).c_str())) m_streamForFilter = emuStream; ImGui::SameLine();
        if(ImGui::SmallButton(fmt::format("Seek###Seek{0}", emuStream->getId()).c_str())) emuStream->seek(m_seek);

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

        //if(ImGui::SmallButton(fmt::format("A1# ###A1S{0}", m_pianoWaveform->getId()).c_str())) {conf->frequency = esnd::Waveform::A1_SHARP; m_pianoWaveform->refresh(); m_playPiano = true; }
        //if(ImGui::SmallButton(fmt::format("B1###B1{0}", m_pianoWaveform->getId()).c_str())) {conf->frequency = esnd::Waveform::B1; m_pianoWaveform->refresh(); m_playPiano = true; }
        //if(m_playPiano)
        //    m_pianoWaveform->play();
        //else
        //    m_pianoWaveform->stop();
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
    }
    ImGui::End();
}

void esnddemo::ProgramManager::drawFilterForm()
{
    std::string filterid = (m_streamForFilter == nullptr) ? "" : m_streamForFilter->getId();
    std::string imguiId = (m_streamForFilter == nullptr) ? "Filters###Filters" : fmt::format("Filters ({0})###Filters", filterid);
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