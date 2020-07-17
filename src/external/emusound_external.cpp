//
// Created by robin on 28.03.2020.
//

#include "../../include/EmusoundConfig.h"

#ifdef USE_FLAC
    #define DR_FLAC_IMPLEMENTATION
    #include "../../include/external/dr_flac.h"  /* Enables FLAC decoding. */
#endif

#ifdef USE_MP3
    #define DR_MP3_IMPLEMENTATION
    #include "../../include/external/dr_mp3.h"   /* Enables MP3 decoding. */
#endif

#ifdef USE_WAV
    #define DR_WAV_IMPLEMENTATION
    #include "../../include/external/dr_wav.h" /* Enables WAV decoding. */
#endif

//USE_OGG has logic in two places define/undef as a workaround for Windows (MSVC) compilation error
#ifdef USE_OGG
    #define STB_VORBIS_HEADER_ONLY
    #include "../../include/external/stb_vorbis.h"
#endif

#define MINIAUDIO_IMPLEMENTATION
#include "../../include/external/emusound_external.h"

//USE_OGG has logic in two places define/undef as a workaround for Windows (MSVC) compilation error
#ifdef USE_OGG
//#define STB_VORBIS_IMPLEMENTATION
    #undef STB_VORBIS_HEADER_ONLY
    #include "../../include/external/stb_vorbis.h"
#endif