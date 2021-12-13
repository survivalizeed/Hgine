

#include "Audio.h"

Audio::Audio()
    : inited_{ false }
    , loaded_samples{ }
{
    if (BASS_Init(-1, 44100, BASS_DEVICE_8BITS, 0, NULL))
        inited_ = true;
    else
        audio_helpers::PrintBassError("Bass_Init");
}

Audio::~Audio()
{
    for (auto& a : loaded_samples)
        BASS_SampleFree(a.second);
    if (inited_)
        BASS_Free();
}

// Plays the sample (with loading its before)

bool Audio::Play(const std::string& fname, bool repeat)
{
    HSAMPLE hndl = FindLoaded(fname);

    if (!hndl && !(hndl = Load(fname, repeat)))
        return false;

    hndl = BASS_SampleGetChannel(hndl, FALSE);
    if (!hndl)
        return audio_helpers::PrintBassError("BASS_SampleGetChannel");
    BASS_ChannelSetAttribute(hndl, BASS_ATTRIB_VOL, 0.5f);

    if (BASS_ChannelPlay(hndl, FALSE))
        return true;
    else
        return audio_helpers::PrintBassError("BASS_ChannelPlay");
}

// Stops playing the sample in two ways - by immediately and by
// set loop flag to 0, therefore next loop is not come

bool Audio::Stop(const std::string& fname, bool immediately)
{
    HSAMPLE hndl = FindLoaded(fname);

    if (!hndl)
        return audio_helpers::PrintGeneralError(fname + std::string(" not loaded"));

    if (immediately)
        return StopPlayingImmediately(hndl);
    else
        return RemoveLoopFromSample(hndl);
}

// Returns std::string of first finded sample which currently is playing

std::vector<std::string> Audio::NowPlaying(bool only_repeated) const
{
    std::vector<std::string> res{};

    for (const auto& l : loaded_samples)
    {
        auto sample_hndl = l.second;
        auto channels_hndls = GetLoadedChannels(sample_hndl);

        if (IsChannelsPlayingNow(channels_hndls)) {
            if (!only_repeated)
                res.push_back(l.first);
            else
                if (audio_helpers::IsRepeatedSample(sample_hndl)) res.push_back(l.first);
        }
    }
    return res;
}

// Loads sample by std::string, saves to loaded_samples vector and return its HSAMPLE

HSAMPLE Audio::Load(const std::string& fname, bool repeat)
{
    HSAMPLE hndl = FindLoaded(fname);
    if (hndl)
        return audio_helpers::PrintGeneralError(fname + std::string(" already loaded"));

    DWORD flags{};
    if (repeat)
        flags = BASS_SAMPLE_LOOP;
    else
        flags = BASS_SAMPLE_8BITS + BASS_SAMPLE_OVER_POS;
    hndl = BASS_SampleLoad(FALSE, fname.c_str(), 0, 0, 3, flags);

    if (!hndl)
        return audio_helpers::PrintBassError("BASS_SampleLoad");
    else
    {
        loaded_samples.push_back(std::make_pair(fname, hndl));
        return hndl;
    }
}

// Returns HSAMPLE of sample if its were been loaded early

HSAMPLE Audio::FindLoaded(const std::string& fname) const
{
    for (auto& l : loaded_samples)
        if (l.first == fname) return l.second;
    return 0;
}

// Gets vector of HSAMPLEs to all loaded channels of sample

std::vector<HSAMPLE> Audio::GetLoadedChannels(const HSAMPLE& hndl) const
{
    auto  nfo = audio_helpers::GetSampleInfo(hndl);
    auto  ch_list_ptr = std::unique_ptr<HCHANNEL>{ new HCHANNEL[nfo.max] };
    auto* ch_list = ch_list_ptr.get();

    DWORD ch_count{ 0 };
    ch_count = BASS_SampleGetChannels(hndl, ch_list);

    std::vector<HSAMPLE> res{};
    for (DWORD i = 0; i < ch_count; ++i) {
        res.push_back(ch_list[i]);
    }
    return res;
}

// Returns true if at least one channel is playing now

bool Audio::IsChannelsPlayingNow(const std::vector<HSAMPLE>& HSAMPLEs) const
{
    for (const auto& h : HSAMPLEs) {
        auto active = BASS_ChannelIsActive(h);
        if (active) return true;
    }
    return false;
}

// Stop playback of given sample immediately

bool Audio::StopPlayingImmediately(const HSAMPLE& hndl)
{
    HCHANNEL ch = BASS_SampleGetChannel(hndl, FALSE);
    BASS_ChannelSetPosition(ch, 0, BASS_POS_BYTE);
    return BASS_SampleStop(hndl);
}

// Stop playback after end of playing sample and change loop flag 

bool Audio::RemoveLoopFromSample(const HSAMPLE& hndl)
{
    if (!audio_helpers::IsRepeatedSample(hndl))
        return false;

    auto channels_hndls = GetLoadedChannels(hndl);
    for (auto& ch : channels_hndls) {
        if (BASS_ChannelFlags(ch, 0, 0) & BASS_SAMPLE_LOOP) {
            BASS_ChannelFlags(ch, 0, BASS_SAMPLE_LOOP);
            return true;
        }
    }
    return false;
}

bool audio_helpers::IsNowPlaying(const Audio& audio, const std::string& fname)
{
    auto now_playing = audio.NowPlaying(false);

    for (const auto& sound : now_playing) {
        if (sound == fname) return true;
    }
    return false;
}

bool audio_helpers::StopAllNowPlaying(Audio& audio, bool only_repeated)
{
    bool result{ true };
    auto sounds = audio.NowPlaying(only_repeated);

    for (const auto& sound : sounds) {
        if (!audio.Stop(sound)) result = false;
    }
    return result;
}

// Returns true if given sample is looped

bool audio_helpers::IsRepeatedSample(const HSAMPLE& hndl)
{
    auto info = audio_helpers::GetSampleInfo(hndl);
    if (info.flags == BASS_SAMPLE_LOOP + BASS_SAMPLE_SOFTWARE)
        return true;
    else
        return false;
}

BASS_SAMPLE audio_helpers::GetSampleInfo(const HSAMPLE& hndl)
{
    BASS_SAMPLE nfo;
    BASS_SampleGetInfo(hndl, &nfo);
    return nfo;
}

bool audio_helpers::SetSampleInfo(const HSAMPLE& hndl, BASS_SAMPLE& nfo)
{
    return BASS_SampleSetInfo(hndl, &nfo);
}

bool audio_helpers::PrintBassError(const std::string& func_name)
{
    auto err = BASS_ErrorGetCode();
    if (err)
        std::cerr << "Audio error code " << err << " in function " << func_name << '\n';

    return err ? false : true;
}

bool audio_helpers::PrintGeneralError(const std::string& msg)
{
    std::cerr << "Audio error: " << msg << '\n';
    return false;
}