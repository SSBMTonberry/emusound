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
    #set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/osx/frameworks)

    #set(SFML_DEPENDENCIES ${PATH_SFML_DEPEND}/FLAC.framework ${PATH_SFML_DEPEND}/freetype.framework ${PATH_SFML_DEPEND}/ogg.framework ${PATH_SFML_DEPEND}/OpenAL.framework ${PATH_SFML_DEPEND}/vorbis.framework ${PATH_SFML_DEPEND}/vorbisenc.framework ${PATH_SFML_DEPEND}/vorbisfile.framework)
    #set(SFML_DEPENDENCIES ${PATH_SFML_DEPEND}/freetype.framework)
endif()

set(DEMO_SOURCE_FILES main.cpp ProgramManager.cpp ProgramManager.h) #EmuAudioSource.cpp EmuAudioSource.h miniaudio.h)

message(NOTICE "Source dir: ${PROJECT_SOURCE_DIR}")

include_directories(${PROJECT_SOURCE_DIR}../external_libs/include ${PROJECT_SOURCE_DIR}../external_libs/include/libgme
        ${PROJECT_SOURCE_DIR}../external_libs/source/pmgui/src ${PROJECT_SOURCE_DIR}../external_libs/source/sfml/include)

if(ESND_APPLE)
    set(MACOSX_BUNDLE_BUNDLE_NAME EmusoundDemo)
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "robin.emusound.demo")
    set(MACOSX_BUNDLE_INFO_STRING "A demonstration of Emusound")
    #set(MACOSX_BUNDLE_ICON_FILE "AppIcon.icns")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
    #set_source_files_properties(${PROJECT_SOURCE_DIR}/logo/AppIcon.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    add_executable(emusound_demo MACOSX_BUNDLE ${DEMO_SOURCE_FILES})
else()
    add_executable(emusound_demo ${DEMO_SOURCE_FILES})
endif()

if(ESND_LINUX)
    target_link_libraries(emusound_demo emusound pmgui sfml-graphics sfml-window sfml-system pthread dl ${SFML_DEPENDENCIES} ${SFML_REST})
elseif(ESND_WINDOWS)
    target_link_libraries(emusound_demo emusound pmgui sfml-graphics sfml-window sfml-system ${SFML_DEPENDENCIES} ${SFML_REST})
elseif(ESND_APPLE)
    target_link_libraries(emusound_demo emusound pmgui sfml-graphics sfml-window sfml-system pthread dl ${SFML_DEPENDENCIES} ${SFML_REST})
    set_target_properties(emusound_demo PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_FRAMEWORK_IDENTIFIER org.cmake.ExecutableTarget)
endif()