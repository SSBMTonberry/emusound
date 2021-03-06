cmake_minimum_required(VERSION 3.15)
project(emusound)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 9)
set(PROJECT_VERSION_PATCH 0)
set(CMAKE_CXX_FLAGS -DSFML_STATIC)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSFML_STATIC -DESND_DEBUG")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Choose the type of build, options are: Debug Release
RelWithDebInfo MinSizeRel."
            FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEBUG 1)
    message(DEBUGGIN')
else()
    set(RELEASE 1)
endif()

set(ESND_LINUX 0)
set(ESND_WINDOWS 0)
set(ESND_APPLE 0)
set(ESND_MSVC 0)
set(ESND_MINGW 0)

if(UNIX AND NOT APPLE)
    set(ESND_LINUX 1)
elseif(APPLE)
    link_directories(/usr/local/opt/llvm/lib/)
    set(ESND_APPLE 1)
elseif(WIN32)
    set(ESND_WINDOWS 1)
    if(MSVC)
        set(ESND_MSVC 1)
    elseif(MINGW)
        set(ESND_MINGW 1)
    endif()
endif()

#SFML
set(BUILD_SHARED_LIBS OFF) #build SFML with static libs
set(SFML_BUILD_AUDIO OFF)

if(DEBUG)
    message("Adding debug submodules")
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/source/pmgui/src ${PROJECT_SOURCE_DIR}/external_libs/source/pmgui/cmake-build-debug)
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/source/sfml ${PROJECT_SOURCE_DIR}/external_libs/source/sfml/cmake-build-debug)
else()
    message("Adding release submodules")
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/source/pmgui/src ${PROJECT_SOURCE_DIR}/external_libs/source/pmgui/cmake-build-release)
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/source/sfml ${PROJECT_SOURCE_DIR}/external_libs/source/sfml/cmake-build-release)
endif()

option(CLEAR_ESND_CMAKE_CACHE "Clear CMake cache for variables. Activate if you are working on the code. Otherwise: keep it off" OFF)
option(USE_GME_AY "Include support for AY (ZX Spectrum/Amstrad CPC)" ON)
option(USE_GME_GBS "Include support for GBS (Nintendo Game Boy)" ON)
option(USE_GME_GYM "Include support for GYM (Sega Genesis/Mega Drive)" ON)
option(USE_GME_HES "Include support for HES (NEC TurboGrafx-16/PC Engine)" ON)
option(USE_GME_KSS "Include support for KSS (MSX Home Computer/other Z80 systems)" ON)
option(USE_GME_NSF "Include support for NSF (Nintendo NES/Famicom)" ON)
option(USE_GME_NSFE "Include support for NSFE (Nintendo NES/Famicom Extended)" ON)
option(USE_GME_SAP "Include support for SAP (Atari systems using POKEY sound chip)" ON)
option(USE_GME_SPC "Include support for SPC (Super Nintendo/Super Famicom)" ON)
option(USE_GME_VGM "Include support for VGM (Sega Master System/Mark III, Sega Genesis/Mega Drive,BBC Micro)" ON)

option(USE_OGG "Include support for OGG/VORBIS" ON)
option(USE_MP3 "Include support for MP3" ON)
option(USE_WAV "Include support for WAV" ON)
option(USE_FLAC "Include support for FLAC" ON)

option(BUILD_DEMO "Build demo for emusound." ON)

configure_file (
        "${PROJECT_SOURCE_DIR}/EmusoundConfig.h.in"
        "${PROJECT_SOURCE_DIR}/include/EmusoundConfig.h"
)

if(USE_GME_AY)
    set(GME_AY_SOURCE ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ay_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ay_Cpu.cpp
                  ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ay_Emu.cpp)
endif()

if(USE_GME_GBS)
    set(GME_GBS_SOURCE ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gb_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gb_Cpu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gb_Oscs.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gbs_Emu.cpp )
endif()

if(USE_GME_GYM)
    set(GME_GYM_SOURCE ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gym_Emu.cpp)
endif()

if(USE_GME_HES)
    set(GME_HES_SOURCE ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Hes_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Hes_Cpu.cpp
                   ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Hes_Emu.cpp)
endif()

if(USE_GME_KSS)
    set(GME_KSS_SOURCE ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Kss_Cpu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Kss_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Kss_Scc_Apu.cpp)
endif()

if(USE_GME_NSF OR USE_GME_NSFE)
    set(GME_NSF_SOURCE ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Apu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Cpu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Fme7_Apu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Namco_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Oscs.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Vrc6_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nsf_Emu.cpp)
endif()

if(USE_GME_NSFE)
    set(GME_NSFE_SOURCE ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nsfe_Emu.cpp)
endif()

if(USE_GME_SAP)
    set(GME_SAP_SOURCE ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Sap_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Sap_Cpu.cpp
                   ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Sap_Emu.cpp)
endif()

if(USE_GME_SPC)
    set(GME_SPC_SOURCE ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Snes_Spc.cpp
                   ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Spc_Cpu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Spc_Dsp.cpp
                   ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Spc_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Spc_Filter.cpp)
endif()

if(USE_GME_VGM)
    set(GME_VGM_SOURCE ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Sms_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Vgm_Emu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Vgm_Emu_Impl.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ym2413_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ym2612_GENS.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ym2612_MAME.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ym2612_Nuked.cpp)
endif()

set(GME_SOURCE_FILES  ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Blip_Buffer.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Classic_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Data_Reader.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Dual_Resampler.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Effects_Buffer.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Fir_Resampler.cpp  ${PROJECT_SOURCE_DIR}/external_libs/source/gme/gme.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gme_File.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/M3u_Playlist.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Multi_Buffer.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Music_Emu.cpp
        ${GME_AY_SOURCE} ${GME_GBS_SOURCE} ${GME_GYM_SOURCE} ${GME_HES_SOURCE} ${GME_KSS_SOURCE} ${GME_NSF_SOURCE} ${GME_NSFE_SOURCE} ${GME_SAP_SOURCE}
        ${GME_SPC_SOURCE} ${GME_VGM_SOURCE} )

set(SOURCE_FILES include/audio/ISoundStream.h src/data/EmuTrackInfo.cpp include/data/EmuTrackInfo.h
        src/audio/EmuStream.cpp include/audio/EmuStream.h include/Enums.hpp
        src/audio/EmuVoice.cpp include/audio/EmuVoice.h include/audio/EmuConfig.hpp
        include/emusound.h include/audio/filters/ISoundFilter.h
        include/audio/filters/LowpassFilter1.hpp include/audio/filters/emusound_filters.h src/external/emusound_external.cpp
        include/audio/filters/BiquadFilter.hpp include/audio/filters/HighpassFilter1.hpp include/audio/filters/HighpassFilter2.hpp
        include/audio/filters/BandpassFilter.hpp include/audio/filters/PeakingEqFilter.hpp include/audio/filters/NotchingFilter.hpp
        include/audio/filters/LowshelfFilter.hpp include/audio/filters/HighshelfFilter.hpp src/audio/Waveform.cpp
        include/audio/Waveform.h include/audio/WaveformConfig.hpp include/audio/Notes.hpp
        include/audio/Noise.cpp include/audio/Noise.h include/external/dr_mp3.h include/external/dr_flac.h include/external/stb_vorbis.h include/audio/MusicStream.cpp include/audio/MusicStream.h include/audio/MusicConfig.hpp)

include_directories(${PROJECT_SOURCE_DIR}/include/external/libgme/ ${PROJECT_SOURCE_DIR}/include/ ${PROJECT_SOURCE_DIR}/external_libs/source/
        ${PROJECT_SOURCE_DIR}/external_libs/source/pmgui/src ${PROJECT_SOURCE_DIR}/external_libs/source/sfml/include)

add_library(emusound ${SOURCE_FILES} ${GME_SOURCE_FILES})

if(BUILD_DEMO)
    message("Building demo...")
    add_subdirectory(demo)
endif()

if(CLEAR_ESND_CMAKE_CACHE)
    unset(USE_GME_AY CACHE)
    unset(USE_GME_GBS CACHE)
    unset(USE_GME_GYM CACHE)
    unset(USE_GME_HES CACHE)
    unset(USE_GME_KSS CACHE)
    unset(USE_GME_NSF CACHE)
    unset(USE_GME_NSFE CACHE)
    unset(USE_GME_SAP CACHE)
    unset(USE_GME_SPC CACHE)
    unset(USE_GME_VGM CACHE)

    unset(USE_OGG CACHE)
    unset(USE_MP3 CACHE)
    unset(USE_WAV CACHE)
    unset(USE_FLAC CACHE)

    unset(BUILD_SHARED_LIBS CACHE) #Must clear the cache to detect changes in this variable
    unset(BUILD_DEMO CACHE)
endif()

unset(CLEAR_ESND_CMAKE_CACHE CACHE)