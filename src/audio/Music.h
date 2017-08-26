#ifndef MUSIC_H
#define MUSIC_H

#include "SDL_mixer.h"
#include <memory>
#include "../managers/ResourceManager.h"

class Music
{
public:
	Music();
	Music(const char* file);
	void Play(int times);
	void Stop();
	void Open(const char* file);
	bool IsOpen();
	bool IsPlaying();
private:
	std::shared_ptr<Mix_Music> music;
};

#endif
