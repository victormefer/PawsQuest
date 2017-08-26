#include "GravityManager.h"
#include "EntityManager.h"
#include "CollisionManager.h"
#include "../physics/Rect.h"
#include "../components/TransformComponent.h"
#include "../components/GravityComponent.h"
#include "../components/MoveComponent.h"
#include "../components/PlayerStateComponent.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
GravityManager::GravityManager() {

}

/*************************************************************
 *
 * ManageGravity percorre o mapa de entidades buscando
 * aquelas que tem o gravityComponent e agindo sobre elas
 *
 *************************************************************/
void GravityManager::ManageGravity() {
	for (auto it0 = EntityManager::mapEntity.begin(); it0 != EntityManager::mapEntity.end(); ++it0)
	{
		for (auto it = it0->second.begin(); it != it0->second.end(); ++it)
		{
			if (it->second->HaveComponent("GravityComponent"))
			{
				if(it->second->GetComponent<GravityComponent>("GravityComponent")->IsEnable())
				{
					if(!CollisionManager::Grounded(it->second))
					{
						if(it->second->GetName() == "Player" ){
							if (it->second->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() != PlayerStateComponent::HANGING)
							{
								it->second->GetComponent<MoveComponent>("MoveComponent")->Falling();
								it->second->GetComponent<GravityComponent>("GravityComponent")->isGrounded = false;
							}
						}else if( it->second->GetName() == "Nut"){
							it->second->GetComponent<MoveComponent>("MoveComponent")->Falling();
							it->second->GetComponent<GravityComponent>("GravityComponent")->isGrounded = false;
						}else{
							it->second->GetComponent<TransformComponent>("TransformComponent")->AddToPos(Point(0,10));
							it->second->GetComponent<GravityComponent>("GravityComponent")->isGrounded = false;
						}
					}

					else
					{
						it->second->GetComponent<GravityComponent>("GravityComponent")->isGrounded = true;
					}
				}
			}
		}
	}
}
