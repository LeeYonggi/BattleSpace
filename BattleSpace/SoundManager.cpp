#include "DXUT.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
	manager = new CSoundManager;
	manager->Initialize(DXUTGetHWND(), 2);
}


SoundManager::~SoundManager()
{
	Release();
}

void SoundManager::AddSound(string str, wstring fileName)
{
	auto iter = m_Sound.find(str);
	if (iter != m_Sound.end()) return;

	CSound *sound;
	manager->Create(&sound, (LPWSTR)fileName.c_str());

	m_Sound.insert(make_pair(str, sound));
}

void SoundManager::PlayWavSound(string str, bool isLoop)
{
	auto iter = m_Sound.find(str);
	if (iter == m_Sound.end()) return;

	iter->second->Play(0, isLoop);
}

void SoundManager::DuplicatePlay(string str)
{
	auto iter = m_Sound.find(str);
	if (iter == m_Sound.end()) return;

	LPDIRECTSOUNDBUFFER buffer;
	manager->GetDirectSound()->DuplicateSoundBuffer(iter->second->GetBuffer(0), &buffer);

	buffer->SetCurrentPosition(0);
	buffer->Play(0, 0, 0);
}

void SoundManager::Stop(string str)
{
	auto iter = m_Sound.find(str);
	if (iter == m_Sound.end()) return;

	iter->second->Stop();
}

void SoundManager::Release()
{
	for (auto iter : m_Sound)
		SAFE_DELETE(iter.second);
	SAFE_DELETE(manager);
}
