#pragma once
#include "SDL_mixer.h"


enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	bool Load(const char* FileName, sound_type type);
	void InitAll();
	void PlayMusic(const char* FileName,int loop);
	void PlaySound(const char* FileName,int loop);
	void TurnUpVolume();
	void TurnDownVolume();

	static SoundManager* Instance();

private:
	int CurrentVolume= MIX_MAX_VOLUME/2;
	Mix_Music* pMusic = nullptr;
	Mix_Chunk* pSound = nullptr;

	static SoundManager* s_pInstance;
};
