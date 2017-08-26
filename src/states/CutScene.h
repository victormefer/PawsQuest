#ifndef CUTSCENE_H_
#define CUTSCENE_H_

#include <vector>
#include "State.h"
#include "../Timer.h"
#include "../gui/GuiSprite.h"
#include "../audio/Music.h"

class CutScene: public State
{
public:
	CutScene(std::string path, int num, float cd, Music music, int phase);
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
	void SetBossDead();
	void InitBossPhase();
	void SetPlayerDead();
	void StopMusic();
private:
	std::string path;
	Timer time;
	float cd;
	int num;
	int phase;
	GuiSprite bg;
	Music music;
	std::vector<bool> opened;
};

#endif
