# Emusound
A permissive cross-platform sound library for games,
designed to play sound files from old consoles (NES, SNES etc) via
their native file format as if they were regular sound files. 
In addition to this, it is also able to play regular audio files in 
the common formats of either .wav, .mp3, .ogg or .flac. 
Basic sound filters are also supported for all sound files!

There is also support for generating waveform sounds in the format of
square, sine, triangle or sawtooth. You can also generate noise sounds.

Emusound has no external dependencies you need to carry around, and can easily be
statically buildt in to your game executable.

## Supported file types for playback

### Consoles
- AY        - ZX Spectrum/Amstrad CPC
- GBS       - Nintendo Game Boy
- GYM       - Sega Genesis/Mega Drive
- HES       - NEC TurboGrafx-16/PC Engine
- KSS       - MSX Home Computer/other Z80 systems (doesn't support FM sound)
- NSF/NSFE  - Nintendo NES/Famicom (with VRC 6, Namco 106, and FME-7 sound)
- SAP       - Atari systems using POKEY sound chip
- SPC       - Super Nintendo/Super Famicom
- VGM       - Sega Master System/Mark III, Sega Genesis/Mega Drive,BBC Micro

### Regular
- WAV - Waveform Audio File Format
- MP3 - Moving Picture Experts Group, Audio Layer III
- OGG - Ogg audio format
- FLAC - Free Lossless Audio Codec 

## Minimalistic design
Emusound is designed with the minimalist in mind!
If you don't need support for certain formats in your project, you can easily 
remove it from the library during build. This can be configured in the CMakeLists.txt file, or through
the CMake GUI application, for simplicity:

## Demo
There is a demo-application that demonstrates the functionality in emusound.
Even though emusound itself can be built both statically (as .lib/.a) and dynamically (as .dll / .so), the demo requires a static build
to compile. This is controlled by the parameter `BUILD_SHARED_LIBS` in the `CMakeLists.txt`, which is off by default (in other words: static).

NOTE: Press Esc/Escape if you want to exit the application.

## Libraries
Although emusound has everything built in to prevent external dependencies, there are external dependencies used to make
this library possible!

These are:


## Credits

