#pragma once
#include "Singleton.h"

#include "SDKsound.h"
#pragma comment(lib, "dSound.lib")

class SoundManager :
	public Singleton<SoundManager>
{
public:
	SoundManager();
	virtual ~SoundManager();

private:
	CSoundManager *manager;
	map<string, CSound*> m_Sound;

public:
	void AddSound(string str, wstring fileName);
	void PlayWavSound(string str, bool isLoop);
	void DuplicatePlay(string str);
	void Stop(string str);
	void Release();

};

#define SOUNDMANAGER SoundManager::GetInstance()