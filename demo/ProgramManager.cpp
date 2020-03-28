//
// Created by robin on 28.03.2020.
//

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
    std::string nsfePath =  "./../../content/demo/gme_tests/test.nsfe";
    std::string nsfPath =   "./../../content/demo/gme_tests/test.nsf";
    std::string spcPath =   "./../../content/demo/gme_tests/test.spc";
    std::string vgmPath =   "./../../content/demo/gme_tests/test.vgm";

    m_nsfeDemo.loadFromFile(nsfePath);
    m_nsfDemo.loadFromFile(nsfPath);
    m_spcDemo.loadFromFile(spcPath);
    m_vgmDemo.loadFromFile(vgmPath);
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
}

void esnddemo::ProgramManager::drawEmuStreamForm()
{
    ImGui::Begin("Audio");
    //NSFE
    ImGui::Text("NSFE"); ImGui::SameLine();
    if(ImGui::SmallButton("Play")) m_nsfeDemo.play(); ImGui::SameLine();
    if(ImGui::SmallButton("Stop")) m_nsfeDemo.stop(); ImGui::SameLine();
    if(ImGui::SmallButton("<-")) m_nsfeDemo.previousTrack(); ImGui::SameLine();
    if(ImGui::SmallButton("->")) m_nsfeDemo.nextTrack();

    //NSF
    ImGui::Text("NSF"); ImGui::SameLine();
    if(ImGui::SmallButton("Play###NSFPlay")) m_nsfDemo.play(); ImGui::SameLine();
    if(ImGui::SmallButton("Stop###NSFStop")) m_nsfDemo.stop(); ImGui::SameLine();
    if(ImGui::SmallButton("<-###NSF<-")) m_nsfDemo.previousTrack(); ImGui::SameLine();
    if(ImGui::SmallButton("->###NSF->")) m_nsfDemo.nextTrack();

    //SPC
    ImGui::Text("SPC"); ImGui::SameLine();
    if(ImGui::SmallButton("Play###SPCPlay")) m_spcDemo.play(); ImGui::SameLine();
    if(ImGui::SmallButton("Stop###SPCStop")) m_spcDemo.stop(); ImGui::SameLine();
    if(ImGui::SmallButton("<-###SPC<-")) m_spcDemo.previousTrack(); ImGui::SameLine();
    if(ImGui::SmallButton("->###SPC->")) m_spcDemo.nextTrack();

    //VGM
    ImGui::Text("VGM"); ImGui::SameLine();
    if(ImGui::SmallButton("Play###VGMPlay")) m_vgmDemo.play(); ImGui::SameLine();
    if(ImGui::SmallButton("Stop###VGMStop")) m_vgmDemo.stop(); ImGui::SameLine();
    if(ImGui::SmallButton("<-###VGM<-")) m_vgmDemo.previousTrack(); ImGui::SameLine();
    if(ImGui::SmallButton("->###VGM->")) m_vgmDemo.nextTrack();

    if(ImGui::Button("STOP!", {100, 40}))
    {
        m_nsfeDemo.stop();
        m_nsfDemo.stop();
        m_spcDemo.stop();
        m_vgmDemo.stop();
    }

    ImGui::End();
}

void esnddemo::ProgramManager::drawAudioManagerForm()
{
    ImGui::Begin("AudioManager");
    std::vector<std::string> sounds = AudioManager::get()->getSoundIdList();
    std::vector<std::string> music = AudioManager::get()->getMusicIdList();
    std::vector<std::string> emuStreams = AudioManager::get()->getEmuStreamIdList();

    ImGui::Text("SOUNDS:");
    for(const auto &str : sounds)
    {
        ImGui::Text(str.c_str()); ImGui::SameLine();
        std::string play = fmt::format("Play###play_sound_{0}", str);
        std::string stop = fmt::format("Stop###stop_sound_{0}", str);
        std::string remove = fmt::format("Remove###remove_sound_{0}", str);

        if (ImGui::SmallButton(play.c_str())) AudioManager::get()->getSound(str)->play();
        ImGui::SameLine();
        if (ImGui::SmallButton(stop.c_str()))  AudioManager::get()->getSound(str)->stop();
        ImGui::SameLine();
        if (ImGui::SmallButton(remove.c_str()))  AudioManager::get()->removeSound(str);
        //ImGui::SameLine();
        //if (ImGui::SmallButton("<-")) m_nsfeDemo.previousTrack();
        //ImGui::SameLine();
        //if (ImGui::SmallButton("->")) m_nsfeDemo.nextTrack();
    }

    ImGui::Text("MUSIC:");
    for(const auto &str : music)
    {
        ImGui::Text(str.c_str()); ImGui::SameLine();
        std::string play = fmt::format("Play###play_music_{0}", str);
        std::string stop = fmt::format("Stop###stop_music_{0}", str);
        std::string remove = fmt::format("Remove###remove_music_{0}", str);

        if (ImGui::SmallButton(play.c_str())) AudioManager::get()->getMusic(str)->play();
        ImGui::SameLine();
        if (ImGui::SmallButton(stop.c_str()))  AudioManager::get()->getMusic(str)->stop();
        ImGui::SameLine();
        if (ImGui::SmallButton(remove.c_str()))  AudioManager::get()->removeMusic(str);
        //ImGui::SameLine();
        //if (ImGui::SmallButton("<-")) m_nsfeDemo.previousTrack();
        //ImGui::SameLine();
        //if (ImGui::SmallButton("->")) m_nsfeDemo.nextTrack();
    }

    //SPC
    ImGui::Text("EMU-STREAMS:");
    for(const auto &str : emuStreams)
    {
        ImGui::Text(str.c_str()); ImGui::SameLine();
        std::string play = fmt::format("Play###play_emu_{0}", str);
        std::string stop = fmt::format("Stop###stop_emu_{0}", str);
        std::string prev = fmt::format("<-###prev_emu_{0}", str);
        std::string next = fmt::format("->###next_emu_{0}", str);
        std::string remove = fmt::format("Remove###remove_emu_{0}", str);

        if (ImGui::SmallButton(play.c_str())) AudioManager::get()->getEmuStream(str)->play();
        ImGui::SameLine();
        if (ImGui::SmallButton(stop.c_str())) AudioManager::get()->getEmuStream(str)->stop();
        ImGui::SameLine();
        if (ImGui::SmallButton(prev.c_str())) AudioManager::get()->getEmuStream(str)->previousTrack();
        ImGui::SameLine();
        if (ImGui::SmallButton(next.c_str())) AudioManager::get()->getEmuStream(str)->nextTrack();
        ImGui::SameLine();
        if (ImGui::SmallButton(remove.c_str()))  AudioManager::get()->removeEmuStream(str);
    }
    //if(ImGui::Button("STOP!", {100, 40}))
    //{
    //    m_nsfeDemo.stop();
    //    m_nsfDemo.stop();
    //    m_spcDemo.stop();
    //    m_vgmDemo.stop();
    //}

    ImGui::End();
}