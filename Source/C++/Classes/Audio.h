#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>

// The x64 in the path doesn't matter. The include files are the same
#include "../../Extern/x64/Bass/c/bass.h"

#if _WIN32 || _WIN64
#if _WIN64
#pragma comment(lib,"F:\\C++\\Hgine\\Hgine\\Source\\Extern\\x64\\Bass\\bass.lib")  
#else
#pragma comment(lib,"F:\\C++\\Hgine\\Hgine\\Source\\Extern\\x86\\Bass\\bass.lib")  
#endif
#endif

class Audio
{
private:
	bool inited_;
	std::vector<std::pair<std::string, HSAMPLE>>   loaded_samples;

	HSAMPLE FindLoaded(const std::string& fname) const;
	std::vector<HSAMPLE> GetLoadedChannels(const HSAMPLE&) const;
	bool IsChannelsPlayingNow(const std::vector<HSAMPLE>&) const;
	bool StopPlayingImmediately(const HSAMPLE&);
	bool RemoveLoopFromSample(const HSAMPLE&);

public:

	Audio();
	virtual ~Audio();

	bool Play(const std::string& fname, bool repeat = false);
	bool Stop(const std::string& fname, bool immediately = true);
	HSAMPLE Load(const std::string& fname, bool);
	std::vector<std::string> NowPlaying(bool only_repeated) const;

};

namespace audio_helpers {

	bool      IsNowPlaying(const Audio&, const std::string&);
	bool      StopAllNowPlaying(Audio&, bool only_repeated);

	bool      IsRepeatedSample(const HSAMPLE&);
	BASS_SAMPLE GetSampleInfo(const HSAMPLE&);
	bool      SetSampleInfo(const HSAMPLE&, BASS_SAMPLE&);
	bool      PrintBassError(const std::string& func_name = "unnamed");
	bool      PrintGeneralError(const std::string& msg);

}

