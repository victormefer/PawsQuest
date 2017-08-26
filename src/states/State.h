#ifndef STATE_H_
#define STATE_H_

#include "../managers/EntityManager.h"
#include "../Timer.h"
#include <vector>
#include <memory>

class State
{
public:
	State();
	virtual ~State();
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void InitBossPhase() = 0;
	virtual void SetBossDead() = 0;
	virtual void SetPlayerDead() = 0;
	virtual void StopMusic() = 0;
	bool PopRequested();
	bool QuitRequested();
	int number;
protected:
	Timer musicStoped;
	bool quitRequested, popRequested;
};

#endif
