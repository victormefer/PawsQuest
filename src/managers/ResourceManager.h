#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <unordered_map>
#include <string>
#include <sstream>
#include <memory>
#include <exception>
#include "../Game.h"
#include "../exceptions/Exceptions.h"


auto deleteTexture = [] (SDL_Texture* texture)
{
	SDL_DestroyTexture(texture);
};

auto deleteMusic = [] (Mix_Music* music)
{
	Mix_FreeMusic(music);
};

auto deleteSound = [] (Mix_Chunk* chunk)
{
	Mix_FreeChunk(chunk);
};

auto deleteFont = [] (TTF_Font* font)
{
	TTF_CloseFont(font);
};

class ResourceManager
{
public:
	static std::shared_ptr<SDL_Texture> GetImage(std::string file);
	static void ClearImages();

	static std::shared_ptr<Mix_Music> GetMusic(std::string file);
	static void ClearMusic();

	static std::shared_ptr<Mix_Chunk> GetSound(std::string file);
	static void ClearSound();

	static std::shared_ptr<TTF_Font> GetFont(std::string file, int fontSize);
	static void ClearFonts();

private:
	static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;

	static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;

	static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;

	static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;

};


#endif
