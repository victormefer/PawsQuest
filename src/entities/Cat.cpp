#include "Cat.h"
#include "../states/TutorialState.h"
#include "../map/TileMap.h"
#include "../audio/Sound.h"
#include "StillAnimation.h"

/*************************************************************
 *
 * Construtor do gato define todos os componentes utilizados
 * pelo gato
 *
 *************************************************************/
Cat::Cat() : Entity("Cat"), timer(), point(0,0), meow("audio/sons/chefe_1_gato/quando_o_gato_aparece_e_a_batalha_comeca.ogg")
{
	SetTag("Cat");

	// ADD RENDER
	RenderComponent* render = new RenderComponent("img/characters/bosses/cat/cat_sit.png", 6, 0.1);
	render->SetOwner(this);
	AddComponent(render);

	// ADD TRANSFORM
	TransformComponent* transform = new TransformComponent(
			Rect( 10880, 601, GetComponent<RenderComponent>("RenderComponent")->GetWidth(),
			GetComponent<RenderComponent>("RenderComponent")->GetHeight() ), 0, Point(1, 1) );
	transform->SetOwner(this);
	AddComponent(transform);

	state = IDLE;
	platform = 0;
	curVase = -1;
	goingLeft = false;
	vasePlatform = 0;
	vaseThrown = 0;
	vaseFalling = false;
	missesLeft = 3;
	start = false;

	meow.Play(0);

	// for (auto it = EntityManager::mapEntity["Ground"].begin(); it != EntityManager::mapEntity["Ground"].end(); ++it)
	// {
	// 	if (Distance(this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center(),
	// 			it->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center())
	// 		<= 500)
	// 	{
	// 		closeGrounds.emplace_back(it->second);
	// 	}
	// }
}

/*************************************************************
 *
 * Update chama o update dos componentes do gato
 *
 *************************************************************/
void Cat::Update(float dt)
{
	switch(state)
	{
		case IDLE:
			timer.Update(dt);
			if (timer.Get() >= 1)
			{
				curVase = platform == 1 ? curVase - 1 : curVase + 1;
				if (curVase == 3 || curVase < 0)
				{
					platform++;
					curVase = platform == 1 ? 2 : 0;
					if (platform == 3)
						state = DEAD;
					else
						ChangePlatform();
				}
				else
					WalkToVase();
				timer.Restart();
			}
			break;

		case WALKING:
			if (Distance(point, this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center()) >= 5)
			{
				if (!goingLeft)
					this->GetComponent<TransformComponent>("TransformComponent")->AddToPos(Point(CAT_SPEED * dt, 0));
				else
					this->GetComponent<TransformComponent>("TransformComponent")->AddToPos(Point(-CAT_SPEED * dt, 0));
			}
			else
			{
				this->GetComponent<TransformComponent>("TransformComponent")->SetPosition(Rect(
					point.x - this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w / 2,
					this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
					this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
					this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h));
				GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(6);
				GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.1);
				GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/bosses/cat/cat_sit.png");
				state = THROWING;
			}
			break;

		case DESCENDING:
			if (Distance(point, this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center()) >= 5)
			{
				this->GetComponent<TransformComponent>("TransformComponent")->AddToPos(Point(0, CAT_SPEED_DOWN * dt));
			}
			else
			{
				this->GetComponent<TransformComponent>("TransformComponent")->SetPosition(Rect(
					this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x,
					point.y - this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h / 2,
					this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
					this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h));
				GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(6);
				GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.1);
				GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/bosses/cat/cat_sit.png");
				state = THROWING;
			}
			break;

		case THROWING:
			vasePlatform = platform;
			vaseThrown = curVase;
			vaseFalling = true;
			state = IDLE;
			break;

		case DEAD:
			Game::GetInstance().GetCurrentState().SetBossDead();
			meow.Play(0);
			break;
	}


	if (vaseFalling)
	{
		std::ostringstream ss1, ss2;
		ss1 << vasePlatform;
		ss2 << vaseThrown;
		EntityManager::GetInstance().GetEntityByName("Vase" + ss1.str() + "_" + ss2.str())->GetComponent<TransformComponent>
		("TransformComponent")->AddToPos(Point(0, VASE_SPEED * dt));

		Rect rect = EntityManager::GetInstance().GetEntityByName("Vase" + ss1.str() + "_" + ss2.str())->GetComponent<TransformComponent>("TransformComponent")->GetPosition();
		Rect aux(rect.x, rect.y + rect.h - VASE_SPEED * dt, rect.w, VASE_SPEED * dt);

		if (EntityManager::GetInstance().GetEntityByName("Vase" + ss1.str() + "_" + ss2.str())->
			GetComponent<BoxColliderComponent>("BoxColliderComponent")->IsColliding(
				EntityManager::GetInstance().GetEntityByName("Almofadinha")->GetComponent<TransformComponent>("TransformComponent")->GetPosition(),
				aux
				))
		{
			vaseFalling = false;
			EntityManager::GetInstance().removeEntity(EntityManager::GetInstance().GetEntityByName("Vase" + ss1.str() + "_" + ss2.str())->GetId());
		}
		else
		{
			// Checa colisao com tiles de chao abaixo da estante
			for (int i = 168; i <= 174; i++)
			{
				Entity* e = TileMap::AtEntity(i, 17, 0);
				if (e != NULL)
				{
					if(EntityManager::GetInstance().GetEntityByName("Vase" + ss1.str() + "_" + ss2.str())->GetComponent<BoxColliderComponent>("BoxColliderComponent")->IsColliding(
						aux, Rect(i*64, 17*64, 64, 64)))
					{
						EntityManager::GetInstance().removeEntity(EntityManager::GetInstance().GetEntityByName("Vase" + ss1.str() + "_" + ss2.str())->GetId());
						srand(time(NULL));
						int rnd = (rand() % 6) + 1;
						std::ostringstream ss;
						ss << rnd;
						Sound sound = Sound("audio/sons/chefe_1_gato/vazos quebrando/" + ss.str() + ".ogg");
						sound.Play(0);

						switch (vasePlatform*3 + vaseThrown)
						{
							case 0:
							case 8:
								EntityManager::GetInstance().addEntity( new StillAnimation( rect.x, rect.y, 0, "VasoQuebrando", "img/fase_0/copo_de_leite_quebrando.png", 7, 0.12, 0.84, true ) );
								break;
							case 1:
							case 5:
								EntityManager::GetInstance().addEntity( new StillAnimation( rect.x, 17*64 - rect.h, 0, "VasoQuebrando", "img/fase_0/trofeu_quebrando.png", 5, 0.12, 0.6, true ) );
								break;
							case 2:
							case 6:
								EntityManager::GetInstance().addEntity( new StillAnimation( rect.x, 17*64 - rect.h, 0, "VasoQuebrando", "img/fase_0/trofeu2_quebrando.png", 10, 0.12, 1.2, true ) );
								break;
							case 3:
								EntityManager::GetInstance().addEntity( new StillAnimation( rect.x, 17*64 - rect.h, 0, "VasoQuebrando", "img/fase_0/globo_quebrando.png", 10, 0.12, 1.2, true ) );
								break;
							case 4:
								EntityManager::GetInstance().addEntity( new StillAnimation( rect.x, 17*64 - rect.h, 0, "VasoQuebrando", "img/fase_0/Vaso_quebrando.png", 7, 0.12, 0.84, true ) );
								break;
							case 7:
								EntityManager::GetInstance().addEntity( new StillAnimation( rect.x, 17*64 - rect.h, 0, "VasoQuebrando", "img/fase_0/VHSquebrandp.png", 4, 0.12, 0.48, true ) );
								break;
						}

						missesLeft--;
						vaseFalling = false;
						break;
					}
				}
			}
		}
	}

	if (missesLeft <= 0)
	{
		meow.Play(0);
		EntityManager::GetInstance().GetEntityByName("Player")->
				GetComponent<HealthComponent>("HealthComponent")->ModifyCurrentHealth('-', 100);
	}

	GetComponent<RenderComponent>("RenderComponent")->Update(dt);
}


/*************************************************************
 *
 * Andar até ponto do vaso
 *
 *************************************************************/
void Cat::WalkToVase()
{
	std::ostringstream ss1, ss2;
	ss1 << platform;
	ss2 << curVase;
	point = Point( 
		EntityManager::GetInstance().GetEntityByName("Vase" + ss1.str() + "_" + ss2.str())->GetComponent<TransformComponent>
		("TransformComponent")->GetPosition().x,
		EntityManager::GetInstance().GetEntityByName("Vase" + ss1.str() + "_" + ss2.str())->GetComponent<TransformComponent>
		("TransformComponent")->GetPosition().y	+
		EntityManager::GetInstance().GetEntityByName("Vase" + ss1.str() + "_" + ss2.str())->GetComponent<TransformComponent>
		("TransformComponent")->GetPosition().h -
		this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h / 2
		);

	state = WALKING;
	if (GetComponent<TransformComponent>("TransformComponent")->GetPosition().x < point.x)
	{
		GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(true);
		goingLeft = false;
	}
	else
	{
		GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(false);
		goingLeft = true;
	}

	GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(12);
	GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.1);
	GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/bosses/cat/cat_walking.png");
}


/*************************************************************
 *
 * Descer de plataforma
 *
 *************************************************************/
void Cat::ChangePlatform()
{
	state = DESCENDING;
	point = GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center() + Point(0, 92);
	GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(12);
	GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.1);
	GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/bosses/cat/cat_shelves_down.png");
}


/*************************************************************
 *
 * Setar começou boss
 *
 *************************************************************/
void Cat::SetStarted(bool started)
{
	start = started;
}
