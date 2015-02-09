#ifndef AUDIOMANAGER_H_INCLUDED
#define AUDIOMANAGER_H_INCLUDED

#include "NonCopyable.h"
#include "Singleton.h"
#include <SDL_mixer.h>
#include <assert.h>
#include <string>
#include <list>
#include "File.h"
#include <map>
class AudioManager;
typedef Singleton<AudioManager> TheAudioManager;
class AudioManager: public NonCopyable
{
public:
	bool Load(File& file);

	void PlaySoundFromTag(const std::string& sound,int loops=0);
	void PlayMusicFromTag(const std::string& music);


    bool PlayWav(const std::string& name);
    bool PlayWav(const std::string& name,int percentVol);
	bool PlayChunk(Mix_Chunk*,int loops =0);
    bool PlayMus(const std::string& name,int fadeIn);
	bool PlayMusic(Mix_Music*);
    bool IsMusicPlaying();
    void SetMusicVolume(int percent);
    void SetMasterVolume(int percent);
    void StopMusic();
    bool Init();
    void Update();

private:
	typedef std::map<std::string,Mix_Chunk*> ChunkMap;
	typedef std::map<std::string,Mix_Music*> MusicMap;
	ChunkMap chunkMap_;
	MusicMap musicMap_;
    AudioManager();
    std::list<int> audio_flags_;
	std::list<int> preLoad_flags_;
    friend TheAudioManager;
    int audio_rate_;
    Uint16 audio_format_;
    int audio_channels_;
    int audio_buffers_;
};

#endif