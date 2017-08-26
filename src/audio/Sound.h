#ifndef SOUND_H
#define SOUND_H

#include "SDL_mixer.h"
#include <memory>
#include "../managers/ResourceManager.h"

class Sound
{
public:
	Sound();
	Sound(std::string file);
	void Play(int times);
	void Stop();
	void Open(std::string file);
	bool IsOpen();
	bool IsPlaying();
private:
	std::shared_ptr<Mix_Chunk> chunk;
	int channel;
};

#endif
