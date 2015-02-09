#include "AudioManager.h"
#include <iostream>
#include "ReportError.h"

AudioManager::AudioManager()
{
    audio_rate_=22050;
    audio_format_=AUDIO_S16SYS;
    audio_channels_=2;
    audio_buffers_=4096;
}

bool AudioManager::Init()
{
    if(Mix_OpenAudio(audio_rate_,audio_format_,audio_channels_,audio_buffers_)!=0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool AudioManager::Load(File& soundFile)
{
	std::string read;
		while(soundFile.GetString(&read))
		{
			if(read=="SoundName")
			{
				std::string name;
				soundFile.GetString(&name);
				while(soundFile.GetString(&read))
				{
					if(read=="SoundFile")
					{
						std::string path;
						soundFile.GetString(&path);
						Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
						assert(sound);
						chunkMap_[name]=sound;
						break;
					}
				}
			}
			if(read=="MusicName")
			{
				std::string name;
				soundFile.GetString(&name);
				while(soundFile.GetString(&read));
				{
					if(read=="MusicFile")
					{
						std::string path;
						soundFile.GetString(&path);
						Mix_Music* music=Mix_LoadMUS(path.c_str());
						assert(music);
						musicMap_[name]=music;
						break;
					}
				}
			}
		}
		return true;
}

void AudioManager::PlaySoundFromTag(const std::string& name,int loops)
{
	ChunkMap::iterator it=chunkMap_.find(name);
	if(it==chunkMap_.end())
	{
	ReportError("Could not find sound"+name);
	return;
	}
	PlayChunk(it->second,loops);

}

void AudioManager::PlayMusicFromTag(const std::string& music)
{
	MusicMap::iterator it=musicMap_.find(music);
	if(it==musicMap_.end())
	{
	ReportError("Could not find music"+music);
	return;
	}
	PlayMusic(it->second);
}

bool AudioManager::PlayWav(const std::string& filename)
{
    Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
    assert(sound);
    int channel = Mix_PlayChannel(-1,sound,0);
    audio_flags_.push_front(channel);
    return true;
}

bool AudioManager::PlayWav(const std::string& filename, int percentVol)
{
    Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
    assert(sound);
    int channel = Mix_PlayChannel(-1,sound,0);
    Mix_Volume(channel,128/100*percentVol);
    audio_flags_.push_front(channel);
    return true;
}

bool AudioManager::PlayChunk(Mix_Chunk* sound,int loops)
{
	assert(sound);
	int channel =Mix_PlayChannel(-1,sound,0);
	preLoad_flags_.push_back(channel);
	return true;
}
bool AudioManager::PlayMusic(Mix_Music* music)
{
	assert(music);
	int channel=Mix_PlayMusic(music,1);
	audio_flags_.push_front(channel);
	return true;
}
bool AudioManager::PlayMus(const std::string& filename,int fadeIn)
{
    Mix_Music* music=0;
    music=Mix_LoadMUS(filename.c_str());
    assert(music);
    int channel;
    if(fadeIn==0)
    {
        channel = Mix_PlayMusic(music,1);
    }
    else
    {
        channel = Mix_FadeInMusic(music,1,1000*fadeIn);
    }
    std::cout<<SDL_GetError();
    audio_flags_.push_front(channel);
    return true;
}

void AudioManager::Update()
{
    for(std::list<int>::iterator it=audio_flags_.begin();
        it!=audio_flags_.end();++it)
    {
		if(!Mix_Playing((*it)))
		{
			Mix_FreeChunk(Mix_GetChunk((*it)));
		}
    }
}

bool AudioManager::IsMusicPlaying()
{
    return (Mix_PlayingMusic!=0);
}

void AudioManager::SetMusicVolume(int percent)
{
    Mix_VolumeMusic(128/100*percent);
}

void AudioManager::StopMusic()
{
    Mix_HaltMusic();
}
