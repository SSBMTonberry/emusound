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
statically built in to your game executable, without any need for an external .dll-file.

Sounds can be read from files or directly from memory. The files read from memory in the `demo`
has been embedded by using [f2src](https://github.com/SSBMTonberry/f2src) to generate source files
with file data.

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

![alt text](https://github.com/SSBMTonberry/emusound/blob/master/images/emusound_01.png "Emusound CMake GUI") 

## Compiling
Emusound uses CMake for compilation, and should be straightforward to compile on all platforms. Either open the CMakeLists.txt in CMake GUI, 
or use the simple `cmake CMakeLists.txt` command in the root folder of this project. Alternatively you can also open the project in an IDE or code editor like Visual Studio Code and compile from there. Windows, Linux and Mac OSX are all supported.

Before compiling, you'll have to get some submodules to be able to compile the demo. 
The command for this should be `git submodule update --init --recursive`.

## Demo
There is a demo-application that demonstrates the functionality in Emusound.
Even though emusound itself can be built both statically (as .lib/.a) and dynamically (as .dll / .so), the demo requires a static build
to compile. This is controlled by the parameter `BUILD_SHARED_LIBS` in the `CMakeLists.txt`, which is off by default (in other words: static).

NOTE: Press `Esc/Escape` if you want to exit the application. The `STOP!` button for every form will stop all sounds related to the actual form.

![alt text](https://github.com/SSBMTonberry/emusound/blob/master/images/emusound_02.png "Emusound demo Screenshot") 

### Waveforms form
Here you can produce your own Square/Sine/Triangle and Sawtooth sounds. You must press the `Play` button to hear the actual sound. You can change the tone by changing the frequency, or press the `Send to piano` button to be able to press what tone you are looking for, and the frequency will be adjusted based on which tone you choose.

### Emu music form
Here you can play emulated sound files. These files can support several tracks in one file. NSF/NSFE typically has several tracks in the file, but for this example only the `NSFE`has several tracks. You can change tracks with `<-` or `->`. If you press the Filter button, you can apply sound filters to the actual sound. You must manually mark filters as `active` to activate them. The `Seek` button will jump to a specific location in the file. This can be controlled by the common `Seek value` in the bottom of the form.

### Music form
Works the same as the `Emu music` form, but plays regular sound files.

### Filters
When pressing the `Filter` button on a chosen track in the `Emu music` or `Music` form, you can apply sound filters to the audio.
Supported filters are:
- Biquad
- Lowpass
- Highpass 
- Bandpass
- Peaking EQ
- Notching
- Lowshelf
- Highshelf

### Noise
Can produce noise sounds. These can be a bit loud, so be careful when adjusting the `seed/amplitude/volume`.
The npoises supported are:
- White
- Pink
- Brownian

NOTE: The demo uses content from the `emusound/content` folder, and uses relative paths to find the folder. Thus the path of the application must have a position that are relative to the content folder in the same way as in this picture (otherwise the content will not be found):
![alt text](https://github.com/SSBMTonberry/emusound/blob/master/images/emusound_03.png "Emusound demo position") 

## Libraries
Although emusound has everything built in to prevent external dependencies, there are external dependencies used to make
this library possible!

These are:
- [miniaudio](https://github.com/dr-soft/miniaudio) - For playing audio / communicating with audio driver.
- [Game_Music_Emu](http://blargg.8bitalley.com/libs/audio.html#Game_Music_Emu) - Used for emulating the sound chip of each retro console.

Used for the demo application:
- [SFML](https://github.com/SFML/SFML) - For sound streaming, window, clipboard and displaying graphics.
- [Dear ImGui](https://github.com/ocornut/imgui) - For anything GUI related.

## Credits
- [Necrophageon](https://www.youtube.com/watch?v=GPJU85sbDIw&t=5s) - Creator of the music used in the NSF example
- [Juhani Junkala (juhani.junkala@musician.org)](https://www.youtube.com/watch?v=dbACpSy9FWY) - Creator of the music used for ogg/wav/mp3/FLAC examples.
