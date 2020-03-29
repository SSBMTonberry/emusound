cmake_minimum_required(VERSION 3.15)
project(emusound)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)
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
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/source/caudio ${PROJECT_SOURCE_DIR}/external_libs/source/caudio/cmake-build-debug)
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/source/pmgui/src ${PROJECT_SOURCE_DIR}/external_libs/source/pmgui/cmake-build-debug)
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/source/sfml ${PROJECT_SOURCE_DIR}/external_libs/source/sfml/cmake-build-debug)
else()
    message("Adding release submodules")
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/source/caudio ${PROJECT_SOURCE_DIR}/external_libs/source/caudio/cmake-build-release)
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/source/pmgui/src ${PROJECT_SOURCE_DIR}/external_libs/source/pmgui/cmake-build-release)
    add_subdirectory(${PROJECT_SOURCE_DIR}/external_libs/source/sfml ${PROJECT_SOURCE_DIR}/external_libs/source/sfml/cmake-build-release)
endif()

configure_file (
        "${PROJECT_SOURCE_DIR}/EmusoundConfig.h.in"
        "${PROJECT_SOURCE_DIR}/include/EmusoundConfig.h"
)

#configure_file(
#        "${PROJECT_SOURCE_DIR}/external_libs/source/caudio/CMake/Templates/cAudioBuildSettings.h.in"
#        "${PROJECT_SOURCE_DIR}/external_libs/source/caudio/cAudio/include/cAudioBuildSettings.h"
#)


set(GME_SOURCE_FILES ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ay_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ay_Cpu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ay_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Blip_Buffer.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Classic_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Data_Reader.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Dual_Resampler.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Effects_Buffer.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Fir_Resampler.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gb_Apu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gb_Cpu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gb_Oscs.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gbs_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/gme.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gme_File.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Gym_Emu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Hes_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Hes_Cpu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Hes_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Kss_Cpu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Kss_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Kss_Scc_Apu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/M3u_Playlist.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Multi_Buffer.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Music_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Apu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Cpu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Fme7_Apu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Namco_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Oscs.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nes_Vrc6_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nsf_Emu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Nsfe_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Sap_Apu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Sap_Cpu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Sap_Emu.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Sms_Apu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Snes_Spc.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Spc_Cpu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Spc_Dsp.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Spc_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Spc_Filter.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Vgm_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Vgm_Emu_Impl.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ym2413_Emu.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ym2612_GENS.cpp
        ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ym2612_MAME.cpp ${PROJECT_SOURCE_DIR}/external_libs/source/gme/Ym2612_Nuked.cpp )

set(SOURCE_FILES include/audio/ISoundStream.h src/data/EmuTrackInfo.cpp include/data/EmuTrackInfo.h
        src/audio/EmuStream.cpp include/audio/EmuStream.h include/Enums.hpp
        src/audio/EmuVoice.cpp include/audio/EmuVoice.h include/audio/EmuConfig.hpp
        include/emusound.h include/audio/filters/ISoundFilter.h
        include/audio/filters/LowpassFilter1.hpp include/audio/filters/emusound_filters.h src/external/emusound_external.cpp include/audio/filters/BiquadFilter.hpp include/audio/filters/HighpassFilter1.hpp include/audio/filters/HighpassFilter2.hpp include/audio/filters/BandpassFilter.hpp include/audio/filters/PeakingEqFilter.hpp include/audio/filters/NotchingFilter.hpp include/audio/filters/LowshelfFilter.hpp include/audio/filters/HighshelfFilter.hpp)

include_directories(${PROJECT_SOURCE_DIR}/include/external/libgme/ ${PROJECT_SOURCE_DIR}/include/ ${PROJECT_SOURCE_DIR}/external_libs/source/
        ${PROJECT_SOURCE_DIR}/external_libs/source/pmgui/src)
add_library(emusound STATIC ${SOURCE_FILES} ${GME_SOURCE_FILES})

add_subdirectory(demo)

unset(BUILD_SHARED_LIBS CACHE) #Must clear the cache to detect changes in this variable
unset(BUILD_TESTS CACHE) #Must clear the cache to detect changes in this variable
unset(BUILD_DEMO CACHE)