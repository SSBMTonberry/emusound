//
// Created by robin on 28.03.2020.
//

#define DR_FLAC_IMPLEMENTATION
#include "../../include/external/dr_flac.h"  /* Enables FLAC decoding. */
#define DR_MP3_IMPLEMENTATION
#include "../../include/external/dr_mp3.h"   /* Enables MP3 decoding. */
#define DR_WAV_IMPLEMENTATION
#include "../../include/external/dr_wav.h" /* Enables WAV decoding. */

//#define STB_VORBIS_IMPLEMENTATION
#include "../../include/external/stb_vorbis.h"

#define MINIAUDIO_IMPLEMENTATION
#include "../../include/external/emusound_external.h"
