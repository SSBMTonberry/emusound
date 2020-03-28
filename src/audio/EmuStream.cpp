//
// Created by robin on 25.03.2020.
//

#include "../../include/audio/EmuStream.h"




void esnd::onDataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{

    //ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    //std::lock_guard<std::mutex> guard(mutex); //Thread safety (hopefully)

    esnd::EmuStream *stream = (esnd::EmuStream*)pDevice->pUserData;
    if(stream == nullptr)
        return;

    if(stream->getStatus() == esnd::SoundStatus::Playing)
        stream->onGetData(pDevice, pOutput, pInput, frameCount);

    (void)pInput;
}

size_t esnd::onReadCallback(ma_decoder* pDecoder, void* pBufferOut, size_t bytesToRead)
{
    //std::lock_guard<std::mutex> guard(mutex); //Thread safety (hopefully)
    esnd::EmuStream *stream = (esnd::EmuStream*)pDecoder->pUserData;
    if(stream == nullptr)
        return 0;


    if(stream->getStatus() == esnd::SoundStatus::Playing)
        return stream->onRead(pDecoder, pBufferOut, bytesToRead);

    return 0;
}

ma_bool32 esnd::onSeekCallback(ma_decoder* pDecoder, int byteOffset, ma_seek_origin origin)
{
    //std::lock_guard<std::mutex> guard(mutex); //Thread safety (hopefully)
    esnd::EmuStream *stream = (esnd::EmuStream*)pDecoder->pUserData;
    if(stream == nullptr)
        return false;

    return stream->onSeek(pDecoder, byteOffset, origin);
}


esnd::EmuStream::~EmuStream()
{
    //std::lock_guard<std::mutex> guard(m_mutex); //Thread safety (hopefully)
    if(m_emu != nullptr)
    {
        ma_device_uninit(&m_config.device);
        ma_decoder_uninit(&m_config.decoder);

        m_isShuttingDown = true;
        delete m_emu;
        m_emu = nullptr;
    }
}


esnd::EmuStream::EmuStream(const std::string &filename, int track, uint32_t channels, uint32_t sampleRate)
{
    loadFromFile(filename, track, channels, sampleRate);
}

esnd::EmuStream::EmuStream(void *data, size_t size, int track, uint32_t channels, uint32_t sampleRate)
{
    loadFromMemory(data, size, track, channels, sampleRate);
}

esnd::StreamLoadStatus esnd::EmuStream::initialize()
{
    //std::bind(&esnd::EmuStream::onRead, this, std::placeholders::_1, std::placeholders::_2,
    //            std::placeholders::_3)
    //std::function<size_t(ma_decoder *,void *,size_t)> on_read = &esnd::EmuStream::onRead;
    //std::function<ma_bool32(ma_decoder *,int,ma_seek_origin)> on_seek = &esnd::EmuStream::onSeek;

    m_config.initialize(m_channels, m_sampleRate);

    esnd::StreamLoadStatus emustats = initializeEmu();
    if(emustats != esnd::StreamLoadStatus::OK)
        return emustats;

    m_decoderInitStatus = ma_decoder_init_raw(onReadCallback, onSeekCallback, &m_config.decoder,
                                              &m_config.dec_config_in, &m_config.dec_config_out, &m_config.decoder);

    if (m_decoderInitStatus != MA_SUCCESS) {
        return esnd::StreamLoadStatus::DecoderInitError;
    }

    m_config.decoder.pUserData = this;

    m_config.deviceConfig = ma_device_config_init(ma_device_type_playback);
    m_config.deviceConfig.playback.format   = m_config.decoder.outputFormat;
    m_config.deviceConfig.playback.channels = m_config.decoder.outputChannels;
    m_config.deviceConfig.sampleRate        = m_config.decoder.outputSampleRate;
    m_config.deviceConfig.dataCallback      = onDataCallback;
    m_config.deviceConfig.pUserData         = this;//&m_config.decoder;

    if (ma_device_init(NULL, &m_config.deviceConfig, &m_config.device) != MA_SUCCESS) {
        printf("Failed to open playback device.\n");
        ma_decoder_uninit(&m_config.decoder);
        return esnd::StreamLoadStatus::StreamOpenFailure;
    }

    if (ma_device_start(&m_config.device) != MA_SUCCESS) {
        printf("Failed to start playback device.\n");
        ma_device_uninit(&m_config.device);
        ma_decoder_uninit(&m_config.decoder);
        return esnd::StreamLoadStatus::StreamStartFailure;
    }



    return esnd::StreamLoadStatus::OK;
}

esnd::StreamLoadStatus esnd::EmuStream::initializeEmu()
{
    if(m_emu != nullptr)
    {
        delete m_emu;
        m_emu = nullptr;
    }

    esnd::StreamLoadStatus status = esnd::StreamLoadStatus::OK;

    // Determine file type
    gme_type_t file_type;
    //std::string header = gme_identify_header(files_mapper::_SUPER_MARIO_BROS_NSFE); //
    //gme_type_t file_type = gme_identify_extension(header.c_str());

    if(m_loadMode == StreamMode::File)
    {
        if(hasEmuError(gme_identify_file( m_filename.c_str(), &file_type ) )) return esnd::StreamLoadStatus::EmuFileIdentificationError;
    }
    else if(m_loadMode == StreamMode::Memory)
    {
        std::string header = gme_identify_header(m_data);
        file_type = gme_identify_extension(header.c_str());
    }

    if ( !file_type )
    {
        return esnd::StreamLoadStatus::EmuUnsupportedMusicType; //!handleError("Unsupported music type");
    }

    // Create emulator and set sample rate
    m_emu = file_type->new_emu();

    if ( !m_emu )
    {
        return esnd::StreamLoadStatus::EmuOutOfMemory;//!handleError("Out of memory");
    }

    if(hasEmuError( m_emu->set_sample_rate( m_sampleRate ))) return esnd::StreamLoadStatus::EmuInvalidSampleRate;

    if(m_loadMode == StreamMode::File)
    {
        if(hasEmuError(m_emu->load_file(m_filename.c_str()))) return esnd::StreamLoadStatus::EmuFileLoadError;
    }
    else if(m_loadMode == StreamMode::Memory)
    {
        if(hasEmuError(m_emu->load_mem(m_data, m_dataSize))) return esnd::StreamLoadStatus::EmuMemoryLoadError;
    }

    m_numberOfTracks = gme_track_count(m_emu);
    if(hasEmuError(m_emu->start_track( m_track ))) return esnd::StreamLoadStatus::EmuInvalidTrack;

    //Load tracks
    for(int i = 0; i < m_numberOfTracks; ++i)
    {
        m_tracks.emplace_back();
        bool success = m_tracks[i].load(m_emu, i);
        if(!success)
            status = esnd::StreamLoadStatus::EmuErrorLoadingTrackData;
            //SystemLog::get()->addError(fmt::format("Error loading track: {0}: {1}", i, m_tracks[i].getErrorText()));
    }

    float tempo = m_tracks[m_track].getTempo();
    setTempo(tempo);
    m_emu->ignore_silence(); //This makes sure the music doesn't stop when all channels are muted.

    const char **voice_names = m_emu->voice_names();
    int i = 0;
    m_voices.clear();
    while (*voice_names)
    {
        int voices = m_emu->voice_count();
        if (i < voices)
        {
            auto item = m_voices.emplace_back(m_emu, i, *voice_names++, false); //, hotkey);
            //m_voices[m_voices.size()-1].setTooltip(fmt::format("Hotkey: <Alt>+{0}", i+1));
            ++i;
        }
        else
            break;
    }

    //m_equalizer.initialize(m_emu);
    this->pause();

    return status;
}

void esnd::EmuStream::muteChannel(int channelNo, bool mute)
{
    if(channelNo < m_voices.size())
    {
        m_voices[channelNo].setMuted(mute);
        m_emu->mute_voice(channelNo, mute);
    }
}

void esnd::EmuStream::toggleMuteChannel(int channelNo)
{
    if(channelNo < m_voices.size())
    {
        m_voices[channelNo].toggleMute();
        m_emu->mute_voice(channelNo, m_voices[channelNo].isMuted());
    }
}

void esnd::EmuStream::unmuteAllChannels()
{
    m_emu->mute_voices(0);
    for(auto const &channel : m_voices)
    {
        muteChannel(channel.getChannelNo(), false);
    }
}

void esnd::EmuStream::setTempo(float tempo)
{
    if(m_emu != nullptr)
    {
        m_tracks[m_track].setTempo(tempo);
        m_emu->set_tempo(tempo);
    }
}

void esnd::EmuStream::setTrack(int track)
{
    m_track = track;
    if(m_emu != nullptr)
    {
        m_emu->start_track(m_track);
        //handleError(m_emu->start_track(m_track));
    }
}

void esnd::EmuStream::setId(const std::string &id)
{
    m_id = id;
}

void esnd::EmuStream::setNumberOfPlays(int numberOfPlays)
{
    m_numberOfPlays = numberOfPlays;
}

void esnd::EmuStream::incrementNumberOfPlays()
{
    ++m_numberOfPlays;
}

void esnd::EmuStream::nextTrack()
{
    m_track = ((m_track + 1) > m_numberOfTracks - 1) ? 0 : m_track + 1;
    setTrack(m_track);
}

void esnd::EmuStream::previousTrack()
{
    m_track = ((m_track-1 < 0) && m_numberOfTracks > 0) ? m_numberOfTracks - 1 : m_track - 1;
    setTrack(m_track);
}

int esnd::EmuStream::getTimePlayed() const
{
    return m_timePlayed;
}

int *esnd::EmuStream::getTimePlayedPtr()
{
    return &m_timePlayed;
}

size_t esnd::EmuStream::getNumberOfVoices()
{
    return m_voices.size();
}

std::vector<esnd::EmuVoice> *esnd::EmuStream::getVoices()
{
    return &m_voices;
}

const esnd::EmuTrackInfo &esnd::EmuStream::getInfoFromCurrentTrack() const
{
    return (m_numberOfTracks > 0) ? m_tracks[m_track] : m_emptyTrack;
}

const std::vector<esnd::EmuTrackInfo> &esnd::EmuStream::getTracks() const
{
    return m_tracks;
}

//EmuEqualizer *getEqualizer()
// {


esnd::StreamMode esnd::EmuStream::getLoadMode() const
{
    return m_loadMode;
}

const std::string &esnd::EmuStream::getFilename() const
{
    return m_filename;
}

int esnd::EmuStream::getTrack() const
{
    return m_track;
}

void *esnd::EmuStream::getData() const
{
    return m_data;
}

size_t esnd::EmuStream::getDataSize() const
{
    return m_dataSize;
}

int esnd::EmuStream::getNumberOfTracks() const
{
    return m_numberOfTracks;
}

const std::string &esnd::EmuStream::getId() const
{
    return m_id;
}

int esnd::EmuStream::getNumberOfPlays() const
{
    return m_numberOfPlays;
}

bool esnd::EmuStream::isValid() const
{
    return m_isValid;
}

//Overridden

esnd::StreamLoadStatus esnd::EmuStream::loadFromFile(const std::string &filename, int track, uint32_t channels, uint32_t sampleRate)
{
    m_track = track;
    return loadFromFile(filename, channels, sampleRate);
}

esnd::StreamLoadStatus esnd::EmuStream::loadFromMemory(void *data, size_t size, int track, uint32_t channels, uint32_t sampleRate)
{
    m_track = track;
    return loadFromMemory(data, size, channels, sampleRate);
}

esnd::StreamLoadStatus esnd::EmuStream::loadFromFile(const std::string &filename, uint32_t channels, uint32_t sampleRate)
{
    m_loadMode = StreamMode::File;
    m_filename = filename;
    m_channels = channels;
    m_sampleRate = sampleRate;
    return initialize();
}

esnd::StreamLoadStatus esnd::EmuStream::loadFromMemory(void *data, size_t size, uint32_t channels, uint32_t sampleRate)
{
    m_loadMode = StreamMode::Memory;
    m_data = data;
    m_dataSize = size;
    m_channels = channels;
    m_sampleRate = sampleRate;
    return initialize();
}

void esnd::EmuStream::play()
{
    m_status = SoundStatus::Playing;
}

void esnd::EmuStream::pause()
{
    m_status = SoundStatus::Paused;
}

void esnd::EmuStream::stop()
{
    m_status = SoundStatus::Stopped;
    seek(0);
}

void esnd::EmuStream::seek(int offset)
{
    ma_decoder_seek_to_pcm_frame(&m_config.decoder, offset);
}

esnd::SoundStatus esnd::EmuStream::getStatus() const
{
    return m_status;
}

size_t esnd::EmuStream::onRead(ma_decoder *pDecoder, void *pBufferOut, size_t bytesToRead)
{
    //std::lock_guard<std::mutex> guard(m_mutex);
    size_t bufferSize = bytesToRead / 2;
    m_emu->play(bufferSize, (short*) pBufferOut);

    int filterStatus = processFilters(pBufferOut, bufferSize, pBufferOut);

    ma_apply_volume_factor_pcm_frames(pBufferOut, bufferSize / 2, ma_format_s16, 2, 1.0f);

    return bufferSize;
}

ma_bool32 esnd::EmuStream::onSeek(ma_decoder *pDecoder, int byteOffset, ma_seek_origin origin)
{
    //std::lock_guard<std::mutex> guard(m_mutex);
    int toSeek = byteOffset / 4;
    blargg_err_t error = m_emu->seek(toSeek);

    return error == nullptr;
}

void esnd::EmuStream::onGetData(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
{
    //std::lock_guard<std::mutex> guard(m_mutex);

    size_t bufferRead = ma_decoder_read_pcm_frames(&m_config.decoder, pOutput, frameCount);
}

uint32_t esnd::EmuStream::getChannelCount() const
{
    return m_channels;
}

uint32_t esnd::EmuStream::getSampleRate() const
{
    return m_sampleRate;
}

const esnd::EmuConfig &esnd::EmuStream::getConfig() const
{
    return m_config;
}

Music_Emu *esnd::EmuStream::getEmu() const
{
    return m_emu;
}

bool esnd::EmuStream::hasEmuError(gme_err_t emuError)
{
    return emuError != nullptr;
}
