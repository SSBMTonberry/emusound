cmake_minimum_required(VERSION 3.15)
project(emusound_demo)

set(CMAKE_CXX_STANDARD 17)

set(GME_SOURCE_FILES ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Ay_Apu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Ay_Cpu.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Ay_Emu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Blip_Buffer.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Classic_Emu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Data_Reader.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Dual_Resampler.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Effects_Buffer.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Fir_Resampler.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Gb_Apu.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Gb_Cpu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Gb_Oscs.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Gbs_Emu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/gme.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Gme_File.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Gym_Emu.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Hes_Apu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Hes_Cpu.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Hes_Emu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Kss_Cpu.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Kss_Emu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Kss_Scc_Apu.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/M3u_Playlist.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Multi_Buffer.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Music_Emu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Nes_Apu.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Nes_Cpu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Nes_Fme7_Apu.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Nes_Namco_Apu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Nes_Oscs.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Nes_Vrc6_Apu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Nsf_Emu.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Nsfe_Emu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Sap_Apu.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Sap_Cpu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Sap_Emu.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Sms_Apu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Snes_Spc.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Spc_Cpu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Spc_Dsp.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Spc_Emu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Spc_Filter.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Vgm_Emu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Vgm_Emu_Impl.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Ym2413_Emu.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Ym2612_GENS.cpp
        ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Ym2612_MAME.cpp ${PROJECT_SOURCE_DIR}/../external_libs/source/gme/Ym2612_Nuked.cpp)

set(SOURCE_FILES main.cpp miniaudio.h dr_wav.h) #EmuAudioSource.cpp EmuAudioSource.h miniaudio.h)

include_directories(../external_libs/include ../external_libs/include/libgme)

add_executable(emusound_demo ${SOURCE_FILES} ${GME_SOURCE_FILES})

#message("Brolo: ${PROJECT_SOURCE_DIR}/../external_libs/lib/linux/libsoloud-s-d.a")

target_link_libraries(emusound_demo ${PROJECT_SOURCE_DIR}/../external_libs/lib/linux/libsoloud-s-d.a pthread asound dl)