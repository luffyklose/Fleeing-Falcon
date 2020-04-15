#include "SoundManager.h"
#include <iostream>

SoundManager* SoundManager::s_pInstance = NULL;

SoundManager* SoundManager::Instance()
{
	if (s_pInstance == 0)
	{
		s_pInstance = new SoundManager();
	}

	return s_pInstance;
}

SoundManager::SoundManager()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout<<"SDL_mixer could not initialize!"<<std::endl;
	}
}

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}

bool SoundManager::Load(const char* FileName, sound_type type)
{
	if (type == SOUND_MUSIC)
	{
		pMusic = Mix_LoadMUS(FileName);

		if (pMusic == 0)
		{
			std::cout << "Music Load Failed!" << std::endl;
			return false;
		}

		return true;
	}
	else if (type == SOUND_SFX)
	{
		pSound = Mix_LoadWAV(FileName);
		if (pSound == 0)
		{
			std::cout << "Sound:" << FileName << " Load Failed!" << std::endl;
			return false;
		}
		return true;
	}

	return false;
}

void SoundManager::InitAll()
{
	if (!Load("assest/Battle_BGM.wav", SOUND_MUSIC))
	{
		std::cout<<"MUSIC LOAD FAILED"<<std::endl;
	}

	if (!Load("assest/FalconFire.wav", SOUND_SFX))
	{
		std::cout << "FALCON FIRE SFX LOAD FAILED" << std::endl;
	}
	if (!Load("assest/FighterFire.wav", SOUND_SFX))
	{
		std::cout << "FIGHTER FIRE SFX LOAD FAILED" << std::endl;
	}
	if (!Load("assest/Ding.wav", SOUND_SFX))
	{
		std::cout << "DING SFX LOAD FAILED" << std::endl;
	}
}

void SoundManager::PlayMusic(const char* FileName, int loop)
{
	pMusic = Mix_LoadMUS(FileName);
	Mix_PlayMusic(pMusic, loop);
}

void SoundManager::PlaySound(const char* FileName,int loop)
{
	pSound= Mix_LoadWAV(FileName);
	Mix_PlayChannel(-1, pSound, loop);
}

void SoundManager::TurnUpVolume()
{
	if (CurrentVolume < MIX_MAX_VOLUME)
	{
		CurrentVolume++;
		Mix_VolumeMusic(CurrentVolume);
		Mix_Volume(-1, CurrentVolume);
		std::cout << Mix_Volume(-1, -1) << std::endl;
	}
	else
	{
		std::cout << "Already at max volume" << std::endl;
	}
}

void SoundManager::TurnDownVolume()
{
	if (CurrentVolume > 0)
	{
		CurrentVolume--;
		Mix_VolumeMusic(CurrentVolume);
		Mix_Volume(-1, CurrentVolume);
		std::cout << Mix_Volume(-1,-1) << std::endl;
	}
	else
	{
		std::cout << "Already at min volume" << std::endl;
	}
}