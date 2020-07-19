cmake_minimum_required(VERSION 3.15)
project(emusound_demo)

set(CMAKE_CXX_STANDARD 17)

if(ESND_LINUX)
    message("It's linux")
    set(SFML_DEPENDENCIES jpeg X11 Xrandr freetype xcb X11-xcb xcb-randr xcb-image GL)
    set(SFML_REST udev) #libudev
elseif(ESND_WINDOWS)
    if(ESND_MSVC)
        message("USING MSVC")

        if(DEBUG)
            set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/win/debug/msvc/sfml)
        elseif(RELEASE)
            set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/win/release/msvc/sfml)
        endif()
        set(SFML_DEPENDENCIES opengl32.lib winmm.lib gdi32.lib ws2_32.lib)
    else()
        # No support for other compilers for Windows.
    endif()
elseif(ESND_APPLE)
    message("USING CLANG!")
    set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/osx/frameworks)

    set(SFML_DEPENDENCIES ${PATH_SFML_DEPEND}/FLAC.framework ${PATH_SFML_DEPEND}/freetype.framework ${PATH_SFML_DEPEND}/ogg.framework ${PATH_SFML_DEPEND}/OpenAL.framework ${PATH_SFML_DEPEND}/vorbis.framework ${PATH_SFML_DEPEND}/vorbisenc.framework ${PATH_SFML_DEPEND}/vorbisfile.framework)
endif()

set(DEMO_SOURCE_FILES main.cpp ProgramManager.cpp ProgramManager.h) #EmuAudioSource.cpp EmuAudioSource.h miniaudio.h)

message(NOTICE "Source dir: ${PROJECT_SOURCE_DIR}")

include_directories(${PROJECT_SOURCE_DIR}../external_libs/include ${PROJECT_SOURCE_DIR}../external_libs/include/libgme
        ${PROJECT_SOURCE_DIR}../external_libs/source/pmgui/src ${PROJECT_SOURCE_DIR}../external_libs/source/sfml/include)

add_executable(emusound_demo ${DEMO_SOURCE_FILES})

if(ESND_LINUX)
    target_link_libraries(emusound_demo emusound pmgui sfml-graphics sfml-window sfml-system pthread dl ${SFML_DEPENDENCIES} ${SFML_REST})
elseif(ESND_WINDOWS)
    target_link_libraries(emusound_demo emusound pmgui sfml-graphics sfml-window sfml-system ${SFML_DEPENDENCIES} ${SFML_REST})
elseif(ESND_APPLE)
    target_link_libraries(emusound_demo emusound pmgui sfml-graphics sfml-window sfml-system pthread dl ${SFML_DEPENDENCIES} ${SFML_REST})
endif()