#ifndef TUTORIALSTATE_H_
#define TUTORIALSTATE_H_

#include<iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "State.h"
#include "../map/TileMap.h"
#include "../map/TileMap.h"
#include "../map/TileSet.h"
#include "../map/ObjectMap.h"
#include "../map/ColliderMap.h"
#include "../map/ItemsMap.h"
#include "../map/EnemyMap.h"
#include "../gui/Gui.h"
#include "../audio/Music.h"
#include "../gui/GuiSprite.h"
#include "../Timer.h"

class TutorialState: public State
{
public:
	TutorialState();
	~TutorialState();
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
	Timer deadTimer;
	GuiSprite bgSprite;
	bool bossDead;
	bool bossPhase;
	bool playerDead;
	bool playingIntro;
};

#endif
