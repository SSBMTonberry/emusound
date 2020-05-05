# emusound
A permissive cross-platform sound library for games,
designed to play sound files from old consoles (NES, SNES etc) via
their native file format as if they were regular sound files. 
In addition to this, it is also able to play regular audio files in 
the common formats of either .wav, .mp3, .ogg or .flac. 
Basic sound filters are also supported for all sound files!

There is also support for generating waveform sounds in the format of
square, sine, triangle or sawtooth. You can also generate noise sounds.


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