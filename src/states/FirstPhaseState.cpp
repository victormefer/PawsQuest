#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "../entities/Player.h"
#include "../entities/Esquilo.h"
#include "FirstPhaseState.h"
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
FirstPhaseState::FirstPhaseState():
	tileSet(64, 64,"img/fase_1/tilesFase1_320x576.png"),
	tileMap("map/fase_1/tileFase1.txt",&tileSet),
	objectMap("map/fase_1/objectMapFase1.txt"),
	colliderMap("map/fase_1/collisionMapFase1.txt"),
	itemsMap("map/fase_1/itemsMapFase1.txt"),
	enemyMap("map/fase_1/enemyMapFase1.txt"),
	bgMusic("audio/5_primeira_fase/fase_1_chiptune_intro.ogg"),
	bgSound("audio/sons/ambiente_parque/ambiente_parque.ogg"),
	gui_sprite("img/back_load.jpg")
{
	bossDead = false;
	bossPhase = false;
	boss = NULL;
	number = 1;
	quitRequested = false;
	playerDead = false;

	tileMap.Render(Camera::pos.x, Camera::pos.y);


	//player
	playerStarted = false;


	bgMusic.Play(0);
	bgSound.Play(-1);
	playingIntro = true;
	bossDead = false;
	Save::CheckPoint = Point(64*7,1200);
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
FirstPhaseState::~FirstPhaseState()
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
void FirstPhaseState::Update(float dt)
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

//		std::cout << EntityManager::GetInstance().GetEntityByName("Player")->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x << std::endl;
//			std::cout << EntityManager::GetInstance().GetEntityByName("Player")->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y << std::endl;

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

		Game::GetInstance().Push(new CutScene("img/cutscene_2",21,0.25,Music("audio/3_jogando_a_bolinha/jogando_a_bolinha.ogg"),2));
	}
	if (EntityManager::GetInstance().GetEntityByName("Player")->GetComponent<HealthComponent>("HealthComponent")->GetCurrentHealth() <= 0)
	{
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

	if (playingIntro)
	{
		if (!bgMusic.IsPlaying())
		{
			bgMusic = Music("audio/5_primeira_fase/fase_1_chiptune_loop.ogg");
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
void FirstPhaseState::Render()
{
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
void FirstPhaseState::Pause()
{
	bgMusic.Stop();
}

/*************************************************************
 *
 * Resume
 *
 *************************************************************/
void FirstPhaseState::Resume()
{
	bgMusic.Play(-1);
}

/*************************************************************
 *
 * SetBossDead
 *
 *************************************************************/
void FirstPhaseState::SetBossDead()
{
	bossDead = true;
}

/*************************************************************
 *
 * InitBossPhase
 *
 *************************************************************/
void FirstPhaseState::InitBossPhase()
{
	Camera::Unfollow();
	Camera::pos.y -= 128;
	//INIT BOSS
	boss = new Esquilo(EntityManager::GetInstance().GetEntityByName("Arvore_esquilo")->
			GetComponent<TransformComponent>("TransformComponent")->GetPosition().x + 129,
			EntityManager::GetInstance().GetEntityByName("Arvore_esquilo")->
			GetComponent<TransformComponent>("TransformComponent")->GetPosition().y + 87-52);
	EntityManager::GetInstance().addEntity(boss);
	bossPhase = true;
}

/*************************************************************
 *
 * InitBossPhase
 *
 *************************************************************/
void FirstPhaseState::SetPlayerDead()
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
void FirstPhaseState::StopMusic()
{
	bgMusic.Stop();
	musicStoped.Update(Game::GetInstance().GetDeltaTime());
}
