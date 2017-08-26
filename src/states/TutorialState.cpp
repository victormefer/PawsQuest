#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "../entities/Player.h"
#include "../entities/Ratazana.h"
#include "../entities/MinionRatazana.h"
#include "../entities/Cat.h"
#include "TutorialState.h"
#include "CutScene.h"
#include "StateData.h"
#include "../managers/EntityManager.h"
#include "../managers/CollisionManager.h"
#include "../components/RenderComponent.h"
#include "../components/TransformComponent.h"
#include "../managers/InputManager.h"
#include "../managers/MessageManager.h"
#include "../messages/Message.h"
#include "../managers/GravityManager.h"
#include "../components/HealthComponent.h"
#include "../Save.h"
#include "PauseState.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
TutorialState::TutorialState():
	tileSet(64, 64, "img/fase_0/tileset.png"),
	tileMap("map/fase_0/tileMapTutorial.txt",&tileSet),
	objectMap("map/fase_0/objectMapTutorial.txt"),
	colliderMap("map/fase_0/collisionMapTutorial.txt"),
	itemsMap("map/fase_0/itemsMapTutorial.txt"),
	enemyMap("map/fase_0/enemyMapTutorial.txt"),
	bgMusic("audio/4_tutorial/tutorial_intro_loop.ogg"),
	bgSprite("img/fase_0/branquelo_1024x576.png")
{
	bossDead = false;
	bossPhase = false;
	boss = NULL;
	number = 0;
	quitRequested = false;
	//INIT PLAYER
	playerDead = false;
	Entity* player = new Player(64*5, 0, 0);
	EntityManager::GetInstance().addEntity(player);
	tileMap.Render(Camera::pos.x, Camera::pos.y);
	Camera::Follow(EntityManager::GetInstance().GetEntityByName("Player"));
	bgMusic.Play(-1);
	playingIntro = true;
	Save::CheckPoint = Point(64*5,0);

}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
TutorialState::~TutorialState()
{
	// Remove todas as entidades
	for (auto it = EntityManager::GetInstance().mapEntity.begin();
		 it != EntityManager::GetInstance().mapEntity.end(); ++it)
		it->second.clear();
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void TutorialState::Update(float dt)
{
//	std::cout << EntityManager::GetInstance().GetEntityByName("Player")->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x << std::endl;
//	std::cout << EntityManager::GetInstance().GetEntityByName("Player")->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y << std::endl;

	/*************************************************************
	 *
	 * Tempo para o player volta a vida
	 *
	 *************************************************************/
	if(playerDead)
	{
		deadTimer.Update(dt);
		if(deadTimer.Get() > 3.5)
		{
			Camera::Follow(EntityManager::GetInstance().GetEntityByName("Player"));
			EntityManager::GetInstance().GetEntityByName("Player")->GetComponent
				<TransformComponent>("TransformComponent")->SetPosition
				(Rect(Save::CheckPoint.x,Save::CheckPoint.y,64,64));
			EntityManager::GetInstance().GetEntityByName("Player")->GetComponent
				<HealthComponent>("HealthComponent")->ModifyCurrentHealth('+', 100);
			EntityManager::GetInstance().GetEntityByName("Player")->GetComponent
				<PlayerStateComponent>("PlayerStateComponent")->SetState(PlayerStateComponent::IDLE);
			if(boss != NULL)
			{
				boss->Delete();
			}
			bossPhase = false;
			Camera::Follow(EntityManager::GetInstance().GetEntityByName("Player"));
			playerDead = false;
		}
	}


	/*************************************************************
	 *
	 * Confere independente de estar ou nao no boss
	 *
	 *************************************************************/
	if(InputManager::GetInstance().QuitRequested())
		quitRequested = true;

	if(InputManager::GetInstance().KeyPress('b'))
		bossDead = true;

	if(InputManager::GetInstance().KeyPress('p'))
		Game::GetInstance().Push(new PauseState());

	// END STAGE
	if (bossDead)
	{
		StateData data;
		data.stage = 1;
		data.Save();
		popRequested = true;
		Game::GetInstance().Push(new CutScene("img/cutscene_1",22,0.25,
			Music("audio/3_jogando_a_bolinha/jogando_a_bolinha.ogg"),1));
	}

	/*************************************************************
	 *
	 * Antes de chegar no boss
	 *
	 *************************************************************/
	if(!bossPhase)
	{
		Camera::Update(dt);
	}
	/*************************************************************
	 *
	 * Depois de chegar no boss
	 *
	 *************************************************************/
	else
	{

	}

	/*************************************************************
	 *
	 * Musica pausada / despausada
	 *
	 *************************************************************/
	if(musicStoped.Get() > 0)
	{
		musicStoped.Update(dt);
		if(musicStoped.Get() > 8)
		{
			bgMusic.Play(-1);
			musicStoped.Restart();
		}
	}

	/*************************************************************
	 *
	 *  Confere independente de estar ou nao no boss
	 *
	 *************************************************************/
	GravityManager::ManageGravity();
	EntityManager::GetInstance().Update(dt);
	CollisionManager::ManageCollision();
	MessageManager::HandleMessaging();
	EntityManager::GetInstance().removeDeadEntities();
	gui.Update(dt);
}

/*************************************************************
 *
 * Render
 *
 *************************************************************/
void TutorialState::Render()
{
	bgSprite.Render(0,0,0);
	tileMap.Render(Camera::pos.x, Camera::pos.y);
	EntityManager::GetInstance().RenderLayer(1);
	EntityManager::GetInstance().RenderLayer(0);
	gui.Render();
}

/*************************************************************
 *
 * Pause
 *
 *************************************************************/
void TutorialState::Pause()
{
	bgMusic.Stop();
}

/*************************************************************
 *
 * Resume
 *
 *************************************************************/
void TutorialState::Resume()
{
	bgMusic.Play(-1);
}

/*************************************************************
 *
 * SetBossDead
 *
 *************************************************************/
void TutorialState::SetBossDead()
{
	bossDead = true;
}

/*************************************************************
 *
 * InitBossPhase
 *
 *************************************************************/
void TutorialState::InitBossPhase()
{
	Camera::Unfollow();
	//INIT BOSS
	boss = new Cat();
	EntityManager::GetInstance().addEntity(boss);
	bossPhase = true;
}

/*************************************************************
 *
 * SetPlayerDead
 *
 *************************************************************/
void TutorialState::SetPlayerDead()
{
	playerDead = true;
	EntityManager::GetInstance().GetEntityByName("Player")->GetComponent
		<PlayerStateComponent>("PlayerStateComponent")->SetState(PlayerStateComponent::DEAD);
}

/*************************************************************
 *
 * StopMusic
 *
 *************************************************************/
void TutorialState::StopMusic()
{
	bgMusic.Stop();
	musicStoped.Update(Game::GetInstance().GetDeltaTime());
}
