//
// Created by robin on 19.01.2020.
//

#include <iostream>
//#include "caudio/cAudio/include/cAudio.h"
//#include <soloud/soloud_wavstream.h>
#include "EmuAudioSource.h"
//int main()
//{
//    //EmuAudioSource source;
//    std::cout << "Hello, Bro!" << std::endl;
//    return 0;
//}

#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "libgme/gme.h"
#include "libgme/Music_Emu.h"

#include <stdio.h>
#include <vector>

std::vector<signed short> m_samples;
std::string m_track_info;

const long SAMPLE_RATE = 44100;

void handle_error( const char* str )
{
    if ( str )
    {
        printf( "Error: %s\n", str ); getchar();
        exit( EXIT_FAILURE );
    }
}

Music_Emu* m_emu = nullptr;

void initEmu(const std::string & filename)
{
    //long sample_rate = SAMPLE_RATE; //44100 / 2; // number of samples per second
    int track = 1; // index of track to play (0 = first)

    // Determine file type
    gme_type_t file_type;
    //std::string header = gme_identify_header(files_mapper::_SUPER_MARIO_BROS_NSFE); //
    //gme_type_t file_type = gme_identify_extension(header.c_str());
    handle_error( gme_identify_file( filename.c_str(), &file_type ) );
    if ( !file_type )
        handle_error( "Unsupported music type" );

    // Create emulator and set sample rate
    //Music_Emu* emu = file_type->new_emu();
    m_emu = file_type->new_emu();

    if ( !m_emu )
        handle_error( "Out of memory" );
    handle_error( m_emu->set_sample_rate( SAMPLE_RATE ) );

    // Load music file into m_emulator
    //handle_error(m_emu->load_mem(files_mapper::_SUPER_MARIO_BROS_NSFE, files_mapper::_SUPER_MARIO_BROS_NSFE_SIZE));
    handle_error( m_emu->load_file( filename.c_str() ) );
    //handle_error( m_emu->load_m3u( filename_m3u ) );
    //m_emu->load_m3u(filename_m3u);
    // Start track
    handle_error( m_emu->start_track( track ) );
    m_emu->ignore_silence(true);
    // Begin writing to wave file
    //Wave_Writer wave( sample_rate, "test.wav" );
    //wave.enable_stereo();

    size_t totalSize = 0;

    long song_length = 0;
    long play_length = 0;
    int voice_count = m_emu->voice_count();
    const char **voice_names = m_emu->voice_names();

    {
        gme_info_t* info;
        handle_error( gme_track_info( m_emu, &info, track ) );
        printf( "System   : %s\n", info->system );
        printf( "Game     : %s\n", info->game );
        printf( "Author   : %s\n", info->author );
        printf( "Copyright: %s\n", info->copyright );
        printf( "Comment  : %s\n", info->comment );
        printf( "Dumper   : %s\n", info->dumper );
        printf( "Tracks   : %d\n", (int) gme_track_count( m_emu ) );
        printf( "\n" );
        printf( "Track    : %d\n", (int) track + 1 );
        printf( "Name     : %s\n", info->song );
        printf( "Length   : %d\n", info->length);
        //printf( "Length   : %ld:%02ld",
        //        (long) info->length / 1000 / 60, (long) info->length / 1000 % 60 );
        //if ( info->loop_length != 0 )
        //    printf( " (endless)" );
        printf( "\n\n" );
        m_track_info = std::string(info->song) + std::string(" - ") + std::string(info->game); //fmt::format("{0} - {1}. Tracks: {2}", info->song, info->game, gme_track_count( m_emu ));
        play_length = info->play_length;
        gme_free_info( info );
    }

    size_t sampleSize = SAMPLE_RATE * 2;
    m_samples.resize(sampleSize);

    //int i = 1;
    //size_t sampleSize = SAMPLE_RATE * 2;
    //m_samples.resize(sampleSize);
    //while ((song_length = m_emu->tell()) > -1 && song_length <= play_length)// && !m_emu->track_ended()) // < 20 * 1000L )//info->length) //20 * 1000L )
    //    //while ((song_length = m_emu->tell()) > -1 && song_length < 10 * 1000L )//info->length) //20 * 1000L )
    //{
    //    // Sample buffer
    //    bool ended = m_emu->track_ended();
    //
    //    //New experimenting
    //    m_samples.resize(i * sampleSize);
    //    m_emu->play(sampleSize, &m_samples[0]+(sampleSize*(i-1)));
    //    ++i;
//
    //    //wave.write( buf, size );
    //}
//
    //delete m_emu;


}

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) {
        return;
    }

    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount);

    (void)pInput;
}

size_t onRead(ma_decoder* pDecoder, void* pBufferOut, size_t bytesToRead)
{
    m_emu->play(m_samples.size(), &m_samples[0]);
    pBufferOut = &m_samples[0];
    bytesToRead = m_samples.size();
}

ma_bool32 onSeek(ma_decoder* pDecoder, int byteOffset, ma_seek_origin origin)
{

}

int example(int argc, char** argv)
{
    ma_result result;
    ma_decoder decoder;
    ma_device_config deviceConfig;
    ma_device device;

    if (argc < 2) {
        printf("No input file.\n");
        return -1;
    }

    result = ma_decoder_init_file(argv[1], NULL, &decoder);
    if (result != MA_SUCCESS) {
        return -2;
    }

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = decoder.outputFormat;
    deviceConfig.playback.channels = decoder.outputChannels;
    deviceConfig.sampleRate        = decoder.outputSampleRate;
    deviceConfig.dataCallback      = data_callback;
    deviceConfig.pUserData         = &decoder;

    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        printf("Failed to open playback device.\n");
        ma_decoder_uninit(&decoder);
        return -3;
    }

    if (ma_device_start(&device) != MA_SUCCESS) {
        printf("Failed to start playback device.\n");
        ma_device_uninit(&device);
        ma_decoder_uninit(&decoder);
        return -4;
    }

    printf("Press Enter to quit...");
    getchar();

    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);

    return 0;
}

int main(int argc, char** argv)
{
    ma_result result;
    ma_decoder decoder;
    ma_decoder_config dec_config_in = ma_decoder_config_init(ma_format_s16, 2, 44100);
    ma_decoder_config dec_config_out = ma_decoder_config_init(ma_format_s16, 2, 44100);
    ma_device_config deviceConfig;
    ma_device device;

    if (argc < 2) {
        printf("No input file.\n");
        return -1;
    }

    initEmu(argv[1]);

    result = ma_decoder_init_raw(onRead, onSeek, &m_samples[0], &dec_config_in, &dec_config_out, &decoder);//ma_decoder_init_raw(argv[1], NULL, &decoder);

    if (result != MA_SUCCESS) {
        return -2;
    }



    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = decoder.outputFormat;
    deviceConfig.playback.channels = decoder.outputChannels;
    deviceConfig.sampleRate        = decoder.outputSampleRate;
    deviceConfig.dataCallback      = data_callback;
    deviceConfig.pUserData         = &decoder; //&m_samples[0];

    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        printf("Failed to open playback device.\n");
        ma_decoder_uninit(&decoder);
        return -3;
    }

    if (ma_device_start(&device) != MA_SUCCESS) {
        printf("Failed to start playback device.\n");
        ma_device_uninit(&device);
        ma_decoder_uninit(&decoder);
        return -4;
    }

    printf("Press Enter to quit...");
    getchar();

    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);

    delete m_emu;

    return 0;
}