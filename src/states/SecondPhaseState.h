#ifndef SECONDPHASESTATE_H_
#define SECONDPHASESTATE_H_

#include<iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "State.h"
#include "../map/TileMap.h"
#include "../map/TileSet.h"
#include "../map/ObjectMap.h"
#include "../map/ColliderMap.h"
#include "../map/ItemsMap.h"
#include "../map/EnemyMap.h"
#include "../gui/Gui.h"
#include "../audio/Music.h"
#include "../audio/Sound.h"
#include "../gui/GuiSprite.h"
#include "../Timer.h"

class SecondPhaseState: public State
{
public:
	SecondPhaseState();
	~SecondPhaseState();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
	void SetBossDead();
	void InitBossPhase();
	void SetPlayerDead();
	void StopMusic();
private:
	Entity* boss;
	TileSet tileSet;
	TileMap tileMap;
	ObjectMap objectMap;
	ColliderMap colliderMap;
	ItemsMap itemsMap;
	EnemyMap enemyMap;
	Gui gui;
	Music bgMusic;
	Sound bgSound;
	GuiSprite bgSprite;
	bool playingIntro;
	bool bossDead;
	bool bossPhase;
	bool playerDead;
	Timer deadTimer;
	Timer startPlayer;
	bool playerStarted;
	GuiSprite gui_sprite;
};

#endif
