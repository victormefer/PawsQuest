#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "SecondPhaseState.h"
#include "../entities/Player.h"
#include "../entities/Ratazana.h"
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

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
SecondPhaseState::SecondPhaseState():
	tileSet(64, 64,"img/fase_2/tilesFase2_320x128.png"),
	tileMap("map/fase_2/tileMapFase2.txt",&tileSet),
	objectMap("map/fase_2/objectMapFase2.txt"),
	colliderMap("map/fase_2/collisionMapFase2.txt"),
	itemsMap("map/fase_2/itemMapFase2.txt"),
	enemyMap("map/fase_2/enemyMapFase2.txt"),
	bgMusic("audio/9_fase_3/fase_3_intro.ogg"),
	bgSound("audio/sons/ambiente_cidade/ambiente_cidade.ogg"),
	bgSprite("img/fase_0/branquelo_1024x576.png"),
	gui_sprite("img/back_load.jpg")
{
	bossDead = false;
	bossPhase = false;
	boss = NULL;
	number = 2;
	quitRequested = false;
	playerStarted = false;

	// //INIT PLAYER
	// playerDead = false;
	// Entity* player = new Player(0, 0, 2);
	// EntityManager::GetInstance().addEntity(player);

	tileMap.Render(Camera::pos.x, Camera::pos.y);
	itemsMap.Render();

	// Camera::Follow(EntityManager::GetInstance().GetEntityByName("Player"));
	//Camera::pos = Point(26880, 1024);

	bgMusic.Play(0);
	bgSound.Play(-1);
	playingIntro = true;
	Save::CheckPoint = Point(64*5,0);
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
SecondPhaseState::~SecondPhaseState()
{
	// Remove todas as entidades
	for (auto it = EntityManager::GetInstance().mapEntity.begin(); it != EntityManager::GetInstance().mapEntity.end(); ++it)
		it->second.clear();
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void SecondPhaseState::Update(float dt)
{

	startPlayer.Update(dt);
	if(startPlayer.Get() > 5 )
	{
		if(playerStarted == false)
		{

			//INIT PLAYER
			playerDead = false;
			Entity* player = new Player(64*5, 0, 1);
			EntityManager::GetInstance().addEntity(player);

			Camera::Follow(EntityManager::GetInstance().GetEntityByName("Player"));
			playerStarted = true;
		}
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

	if(InputManager::GetInstance().QuitRequested())
	{
		quitRequested = true;
	}

	if(InputManager::GetInstance().KeyPress('b'))
		bossDead = true;


	// END STAGE
	if (bossDead)
	{
		StateData data;
		data.stage = 1;
		data.Save();
		popRequested = true;

		Game::GetInstance().Push(new CutScene("img/cutscene",9,1,Music("audio/3_jogando_a_bolinha/jogando_a_bolinha.ogg"),0));
	}
	if (EntityManager::GetInstance().GetEntityByName("Player")->GetComponent<HealthComponent>("HealthComponent")->GetCurrentHealth() <= 0)
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

	Camera::Update(dt);
	GravityManager::ManageGravity();
	EntityManager::GetInstance().Update(dt);
	CollisionManager::ManageCollision();
	MessageManager::HandleMessaging();
	EntityManager::GetInstance().removeDeadEntities();

	gui.Update(dt);

	if (playingIntro)
	{
		if (!bgMusic.IsPlaying())
		{
			bgMusic = Music("audio/9_fase_3/fase_3_loop.ogg");
			bgMusic.Play(-1);
			playingIntro = false;
		}
	}
	}
}

/*************************************************************
 *
 * Render
 *
 *************************************************************/
void SecondPhaseState::Render()
{
	bgSprite.Render(0,0,0);
	EntityManager::GetInstance().RenderLayer(3);
	EntityManager::GetInstance().RenderLayer(2);
	tileMap.Render(Camera::pos.x, Camera::pos.y);
	EntityManager::GetInstance().RenderLayer(1);
	EntityManager::GetInstance().RenderLayer(0);
	gui.Render();
	if(!playerStarted)
	{
		gui_sprite.Render(0,0);
	}
}

/*************************************************************
 *
 * Pause
 *
 *************************************************************/
void SecondPhaseState::Pause()
{
	bgMusic.Stop();
}

/*************************************************************
 *
 * Resume
 *
 *************************************************************/
void SecondPhaseState::Resume()
{
	bgMusic.Play(-1);
}

/*************************************************************
 *
 * SetBossDead
 *
 *************************************************************/
void SecondPhaseState::SetBossDead()
{
	bossDead = true;
}

/*************************************************************
 *
 * InitBossPhase
 *
 *************************************************************/
void SecondPhaseState::InitBossPhase()
{
	Camera::Unfollow();
	//INIT BOSS
	boss = new Ratazana(27500, 1073);
	EntityManager::GetInstance().addEntity(boss);
	bossPhase = true;
}

/*************************************************************
 *
 * SetPlayerDead
 *
 *************************************************************/
void SecondPhaseState::SetPlayerDead()
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
void SecondPhaseState::StopMusic()
{
	bgMusic.Stop();
	musicStoped.Update(Game::GetInstance().GetDeltaTime());
}
