#pragma once
#include "singletonBase.h"
#include <map>

#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex64_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class SoundManager : public singletonBase<SoundManager>
{
private:
	typedef map<string, Sound**>			arrSounds;
	typedef map<string, Sound**>::iterator	arrSoundsIter;

	typedef map<string, Channel**>				arrChannels;
	typedef map<string, Channel**>::iterator	arrChannelsIter;

private:
	System* _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;

public:
	SoundManager();
	~SoundManager();

	HRESULT Init();
	void Release();
	void Update();

	void AddSound(string keyName, string soundName, bool bgm, bool loop);

	void Play(string keyName, float volume = 1.0f);
	void Stop(string keyName);
	void Pause(string keyName);
	void Resume(string keyName);

	//사운드 이벤트 처리용 (호옥시 몰라)
	bool IsPlaySound(string keyName);
	bool IsPauseSound(string keyName);

};

