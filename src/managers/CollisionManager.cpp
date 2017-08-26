#include "CollisionManager.h"
#include "EntityManager.h"
#include "../map/TileMap.h"
#include "../components/TransformComponent.h"
#include "../components/BoxColliderComponent.h"
#include "../components/PlayerStateComponent.h"
#include "../components/BreakablePlatformComponent.h"
#include "../components/MoveComponent.h"
#include "../components/InputComponent.h"
#include "../Camera.h"
#include "../physics/Rect.h"
#include "../Game.h"
#include "../entities/Ratazana.h"
#include "../entities/Nut.h"
#include "../entities/Esquilo.h"
#include "../entities/MinionRatazana.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
CollisionManager::CollisionManager()
{

}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
CollisionManager::~CollisionManager()
{

}

/*************************************************************
 *
 * ManageCollision apenas entre o Player e outra entidade
 * iterando no mapa para acha-la. Quando a colisao ocorre
 * mandamos uma mensagem para o message manager, e para
 * detectar q a colisao ocorreu usamos o metodo IsColliding
 *
 *************************************************************/
void CollisionManager::ManageCollision()
{
	//bool pushableCollided = false;

	for (auto it = EntityManager::mapEntity["Player"].begin(); it != EntityManager::mapEntity["Player"].end(); ++it)
	{
		if(EntityManager::GetInstance().GetEntityById(it->first)->GetComponent
			<PlayerStateComponent>("PlayerStateComponent")->GetState() == PlayerStateComponent::JUMPING)
		{
			CollisionManager::Ascending(it->second);
		}


		int x, y;
		Point point;
		point = it->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center();
		x = point.x / 64;
		y = point.y / 64;

		for (int i = x - 1; i <= x + 1; i++)
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				Entity* e = TileMap::AtEntity(i, j, 0);
				if (e != NULL)
				{
					if(it->second->GetComponent<BoxColliderComponent>("BoxColliderComponent")->IsColliding(
							it->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition(),
							Rect(i*64, j*64, 64, 64)))
					{
						it->second->SendMessage(new Message(Message::COLLISION_DETECTED, it->second, e));
					}
				}
			}
		}



		for (auto jt0 = EntityManager::mapEntity.begin();
			jt0 != EntityManager::mapEntity.end();
			++jt0)
		{
			for (auto jt = jt0->second.begin(); jt != jt0->second.end(); ++jt)
			{
				if(jt->second->HaveComponent("BoxColliderComponent") && it != jt &&
						IsInside(Rect(Camera::pos.x, Camera::pos.y, 1024, 600),
								jt->second->GetComponent<TransformComponent>("TransformComponent")->
									GetPosition().Center()))
				{
					if(EntityManager::GetInstance().GetEntityById(it->first)->
						GetComponent<BoxColliderComponent>("BoxColliderComponent")->
						IsColliding(
							EntityManager::GetInstance().GetEntityById(it->first)->
							GetComponent<TransformComponent>("TransformComponent")->GetPosition(),
							EntityManager::GetInstance().GetEntityById(jt->first)->
							GetComponent<TransformComponent>("TransformComponent")->GetPosition()
							))
					{
						it->second->SendMessage(new Message(Message::COLLISION_DETECTED, it->second, jt->second));
					}
				}
			}
		}
	}
	for (auto it = EntityManager::mapEntity["Enemy"].begin(); it != EntityManager::mapEntity["Enemy"].end(); ++it)
	{
		for (auto jt0 = EntityManager::mapEntity.begin();
					jt0 != EntityManager::mapEntity.end();
					++jt0)
				{
					for (auto jt = jt0->second.begin(); jt != jt0->second.end(); ++jt)
					{
						if(jt->second->tag == "Prefab")
						{
							if(it->second->GetComponent<BoxColliderComponent>("BoxColliderComponent")->
								IsColliding(
											EntityManager::GetInstance().GetEntityById(it->first)->
											GetComponent<TransformComponent>("TransformComponent")->GetPosition(),
											EntityManager::GetInstance().GetEntityById(jt->first)->
											GetComponent<TransformComponent>("TransformComponent")->GetPosition()
											))
							{

								it->second->SendMessage(new Message(Message::COLLISION_DETECTED, it->second, jt->second));
							}
						}
					}
				}
	}
	for (auto it = EntityManager::mapEntity["Pushable"].begin(); it != EntityManager::mapEntity["Pushable"].end(); ++it)
		{
			if(it->second->GetName() == "Nut"){
				auto jt = EntityManager::GetInstance().GetEntityByName("Arvore_esquilo");

				if(it->second->GetComponent<BoxColliderComponent>("BoxColliderComponent")->
						IsColliding(
									EntityManager::GetInstance().GetEntityById(it->first)->
									GetComponent<TransformComponent>("TransformComponent")->GetPosition(),
									EntityManager::GetInstance().GetEntityById(jt->GetId())->
									GetComponent<TransformComponent>("TransformComponent")->GetPosition()
									))
				{

					it->second->SendMessage(new Message(Message::COLLISION_DETECTED, it->second, jt));
				}
			}

		}

}

/*************************************************************
 *
 * Grounded verifica se o player esta colidindo com o chao
 *
 *************************************************************/
bool CollisionManager::Grounded(Entity* entity)
{
	Rect rect = entity->GetComponent<TransformComponent>("TransformComponent")->GetPosition();
	Rect aux(rect.x, rect.y + rect.h, rect.w, 450 * Game::GetInstance().GetDeltaTime());

	// std::cout << "CHEGOU GROUNDED" << std::endl;

	int x, y;
	Point point;
	point = entity->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center();
	x = point.x / 64;
	y = point.y / 64;

	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (i >= 0 && j >= 0 && i <= TileMap::mapHeight && j <= TileMap::mapWidth)
			{
				Entity* e = TileMap::AtEntity(i, j, 0);

				if (e != NULL)
				{
					if (e->tag == "Ground")
					{
						if(entity->GetComponent<BoxColliderComponent>("BoxColliderComponent")->IsColliding(aux, Rect(i*64, j*64, 64, 64)))
						{
							entity->GetComponent<TransformComponent>("TransformComponent")->
								SetPosition( Rect(
									rect.x,
									e->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y - rect.h,
									rect.w,
									rect.h));
							return true;
						}
					}
					else if (e->tag == "Platform")
					{

						if (entity->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() != PlayerStateComponent::JUMPING &&
								entity->GetComponent<BoxColliderComponent>("BoxColliderComponent")->IsColliding(aux, Rect(i*64, j*64, 64, 64)))
						{
							if(e->HaveComponent("BreakablePlatformComponent"))
								e->GetComponent<BreakablePlatformComponent>("BreakablePlatformComponent")->Break();
							entity->GetComponent<TransformComponent>("TransformComponent")->
							SetPosition(Rect(
								rect.x,
								e->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y - rect.h,
								rect.w,
								rect.h));
							return true;
						}
					}
				}
			}
		}
	}

	if(entity->GetName() == "Player"){
		// GROUND
		for (auto it = EntityManager::mapEntity["Ground"].begin(); it != EntityManager::mapEntity["Ground"].end(); ++it)
		{
			if ( IsInside(Rect(Camera::pos.x, Camera::pos.y, 1024, 600), it->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center()) )
			{
				if (
					entity->GetComponent<BoxColliderComponent>("BoxColliderComponent")->IsColliding(
						EntityManager::GetInstance().GetEntityById(it->first)->
						GetComponent<TransformComponent>("TransformComponent")->GetPosition(),
						aux))
				{
					if(it->second->GetName() == "Spike" || it->second->GetName() == "Nut")
					{
						entity->GetComponent<PlayerStateComponent>("PlayerStateComponent")->
							SetState(PlayerStateComponent::DAMAGED);
					}
					entity->GetComponent<TransformComponent>("TransformComponent")->
						SetPosition( Rect(
							rect.x,
							it->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y - rect.h,
							rect.w,
							rect.h));
					if(it->second->GetName() == "Almofada")
					{
						entity->GetComponent<MoveComponent>("MoveComponent")->Bounce();
					}
					return true;
				}
			}
		}
		// ENEMY
		for (auto it = EntityManager::mapEntity["Enemy"].begin(); it != EntityManager::mapEntity["Enemy"].end(); ++it)
		{
			if ( IsInside(Rect(Camera::pos.x, Camera::pos.y, 1024, 600), it->second->GetComponent
					<TransformComponent>("TransformComponent")->GetPosition().Center()) )
			{
				if (
					entity->GetComponent<BoxColliderComponent>("BoxColliderComponent")->IsColliding(
						EntityManager::GetInstance().GetEntityById(it->first)->
						GetComponent<TransformComponent>("TransformComponent")->GetPosition(),
						aux))
				{
					entity->GetComponent<MoveComponent>("MoveComponent")->Jump();
					if(entity->GetName() == "Player" && entity->GetComponent<PlayerStateComponent>("PlayerStateComponent")
							->GetState() == PlayerStateComponent::FALLING)
					{
						if(it->second->HaveComponent("HealthComponent"))
						{
							it->second->GetComponent<HealthComponent>("HealthComponent")->ModifyCurrentHealth('-',100);
						}
						return true;
					}
				}
			}
		}
		// PUSHABLE
		for (auto it = EntityManager::mapEntity["Pushable"].begin(); it != EntityManager::mapEntity["Pushable"].end(); ++it)
		{
			if ( IsInside(Rect(Camera::pos.x, Camera::pos.y, 1024, 600), it->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center()) )
			{

				if (
					entity->GetComponent<BoxColliderComponent>("BoxColliderComponent")->IsColliding(
						EntityManager::GetInstance().GetEntityById(it->first)->
						GetComponent<TransformComponent>("TransformComponent")->GetPosition(),
						aux))
				{

					entity->GetComponent<TransformComponent>("TransformComponent")->
						SetPosition( Rect(
							rect.x,
							it->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y - rect.h,
							rect.w,
							rect.h));
					return true;
				}
			}
		}
		// BOSS
		for (auto it = EntityManager::mapEntity["Boss"].begin(); it != EntityManager::mapEntity["Boss"].end(); ++it)
		{
			if (
					entity->GetComponent<BoxColliderComponent>("BoxColliderComponent")->IsColliding(
						EntityManager::GetInstance().GetEntityById(it->first)->
						GetComponent<TransformComponent>("TransformComponent")->GetPosition(),
						aux))
			{
				//GAMBIARRA DO ESQUILO
				if((it->second->GetName() == "Esquilo") && (dynamic_cast<Esquilo*>(it->second)->state == Esquilo::DOWN))
				{
					dynamic_cast<Esquilo*>(it->second)->Damage();
					entity->GetComponent<MoveComponent>("MoveComponent")->Jump();
					return true;
				}
				// GAMBIARRA DA RATAZANA
				if(it->second->GetName() == "Ratazana" &&
				   dynamic_cast<Ratazana*>(it->second)->state == Ratazana::WALKING &&
				   it->second->HaveComponent("HealthComponent"))
				{
					it->second->GetComponent<HealthComponent>("HealthComponent")->ModifyCurrentHealth('-',25);
				}
				// GAMBIARRA DOS MINIONS DA RATAZANA
				if(it->second->GetName() == "MinionRatazana" &&
				   dynamic_cast<MinionRatazana*>(it->second)->state == MinionRatazana::WALKING &&
				   it->second->HaveComponent("HealthComponent"))
				{
					std::cout << "col min rata" << std::endl;

					it->second->GetComponent<HealthComponent>("HealthComponent")->ModifyCurrentHealth('-',50);
					std::cout << it->second->GetComponent<HealthComponent>("HealthComponent")->GetCurrentHealth() << std::endl;
					//				if()
	//				{
	//						EntityManager::GetInstance().GetEntityByName("Ratazana")
	//				}
				}
				entity->GetComponent<MoveComponent>("MoveComponent")->Jump();
				return true;
			}
		}
		// PLATFORM
		for (auto it = EntityManager::mapEntity["Platform"].begin(); it != EntityManager::mapEntity["Platform"].end(); ++it)
		{
			if (
					it->second->GetComponent<BoxColliderComponent>("BoxColliderComponent")->IsEnable()
					&& it->second->tag ==  "Platform" &&
					entity->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState()
						!= PlayerStateComponent::JUMPING &&
					entity->GetComponent<BoxColliderComponent>("BoxColliderComponent")->IsColliding(
						EntityManager::GetInstance().GetEntityById(it->first)->
						GetComponent<TransformComponent>("TransformComponent")->GetPosition(),
						aux))
			{
				if(it->second->GetName() == "Breakable")
				{
					std::cout<<"oi"<<std::endl;
					it->second->GetComponent<BreakablePlatformComponent>("BreakablePlatformComponent")->Break();
				}
				entity->GetComponent<TransformComponent>("TransformComponent")->
				SetPosition(Rect(
					rect.x,
					it->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y - rect.h,
					rect.w,
					rect.h));
				return true;
			}
		}
	}
	return false;
}

/*************************************************************
 *
 * Ascending
 *
 *************************************************************/
void CollisionManager::Ascending(Entity* entity)
{
	float up =  entity->GetComponent<MoveComponent>("MoveComponent")->GetVerticalSpeed();
	float speed =  entity->GetComponent<MoveComponent>("MoveComponent")->GetSpeed();


	Rect rect = entity->GetComponent<TransformComponent>("TransformComponent")->GetPosition();
	Rect aux;
	if(speed>=0){
		aux = Rect(rect.x , rect.y, rect.w -speed - 1 , up);
	}else{
		aux = Rect(rect.x + (-speed) +1  , rect.y, rect.w-speed , up);
	}
	//std::cout << rect.x <<'/'  << rect.y <<'/'  << rect.w <<'/'  << rect.h <<'/'
	//		<<std::endl;


	int x, y;
	Point point;
	point = entity->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center();
	x = point.x / 64;
	y = point.y / 64;

	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			Entity* e = TileMap::AtEntity(i, j, 0);
			if (e != NULL)
			{
				if(entity->GetComponent<BoxColliderComponent>("BoxColliderComponent")->IsColliding(aux, Rect(i*64, j*64, 64, 64)) && e->tag == "Ground")
				{
					entity->GetComponent<TransformComponent>("TransformComponent")->
						SetPosition( Rect(
							rect.x,
							e->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y
							+ e->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h,
							rect.w,
							rect.h) );
					entity->GetComponent<InputComponent>("InputComponent")->KillJump();
				}
			}
		}
	}

	// GROUND
	for (auto it = EntityManager::mapEntity["Ground"].begin(); it != EntityManager::mapEntity["Ground"].end(); ++it)
	{
		if ( IsInside(Rect(Camera::pos.x, Camera::pos.y, 1024, 600), it->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center()) )
		{
			if (
				entity->GetComponent<BoxColliderComponent>("BoxColliderComponent")->IsColliding(
					EntityManager::GetInstance().GetEntityById(it->first)->
					GetComponent<TransformComponent>("TransformComponent")->GetPosition(),
					aux))
			{

				if(it->second->GetName() == "Spike")
				{
					entity->GetComponent<PlayerStateComponent>("PlayerStateComponent")->SetState(PlayerStateComponent::DAMAGED);
				}
				entity->GetComponent<TransformComponent>("TransformComponent")->
					SetPosition( Rect(
						rect.x,
						it->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y
						+ it->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h,
						rect.w,
						rect.h) );
				entity->GetComponent<InputComponent>("InputComponent")->KillJump();
			}
		}
	}
}

