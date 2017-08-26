#include "EntityManager.h"
#include "../components/RenderComponent.h"
#include "../components/TransformComponent.h"
#include "../components/PlayerStateComponent.h"
#include "../components/IA_WalkRightLeftComponent.h"
#include "../Camera.h"

EntityManager* EntityManager::instance = NULL;
std::map<std::string, std::map<int,Entity*>> EntityManager::mapEntity;// = {{"", {0,NULL}}};

/*************************************************************
 *
 * Construtor Singleton
 *
 *************************************************************/
EntityManager::EntityManager()
{
	if (instance != NULL){ std::cout<< "Instance != NULL" << std::endl;	}
	else{ instance = this; }
}

/*************************************************************
 *
 * GetInstance
 *
 *************************************************************/
EntityManager& EntityManager::GetInstance()
{
	return *instance;
}

/*************************************************************
 *
 * GetEntityById
 *
 *************************************************************/
Entity* EntityManager::GetEntityById(int id)
{
	for (auto it = mapEntity.begin(); it != mapEntity.end(); ++it)
	{
		try
		{
			return it->second.at(id);
		}
		catch (...)
		{

		}
	}
	return NULL;
	//return mapEntity[id];
}

/*************************************************************
 *
 * GetEntityByName
 *
 *************************************************************/
Entity* EntityManager::GetEntityByName(std::string name)
{
	for (auto it = mapEntity.begin(); it != mapEntity.end(); ++it)
	{
		for (auto ent = it->second.begin(); ent != it->second.end(); ++ent)
		{
			if (ent->second->GetName() == name)
				return ent->second;
		}
	}
	return NULL;
}

/*************************************************************
 *
 * AddEntity
 *
 *************************************************************/
void EntityManager::addEntity(Entity* entity)
{
	//mapEntity[entity->GetId()] = entity;
	mapEntity[entity->tag][entity->GetId()] = entity;
}

/*************************************************************
 *
 * RemoveEntity
 *
 *************************************************************/
void EntityManager::removeEntity(int id)
{
	//mapEntity.erase(id);
	mapEntity[GetEntityById(id)->tag].erase(id);
}

/*************************************************************
 *
 * Size retorna o  tamanho do mapa de entidades
 *
 *************************************************************/
int EntityManager::Size()
{
	int size = 0;
	for (auto it = mapEntity.begin(); it != mapEntity.end(); ++it)
	{
		size += it->second.size();
	}
	return size;
	//return mapEntity.size();
}

/*************************************************************
 *
 * RenderLayer
 *
 *************************************************************/
void EntityManager::RenderLayer(int layer)
{
	switch (layer)
	{
		case 0:
			for (auto it = mapEntity["Layer_0"].begin(); it != mapEntity["Layer_0"].end(); ++it)
			{
				TransformComponent transf = *(it->second->GetComponent<TransformComponent>("TransformComponent"));
				transf.AddToPos( Point(-Camera::pos.x * 0.5, -Camera::pos.y * 0.5) );
				it->second->GetComponent<RenderComponent>("RenderComponent")->Render(&transf);
			}
			break;


		case 1:
			// Camada principal
			for (int i = 0; i < 12; i++)
			{
				std::string tag;
				switch(i)
				{
					case 0:
						tag = "default_tag";
						break;
					case 1:
						tag = "Ground";
						break;
					case 2:
						tag = "Platform";
						break;
					case 3:
						tag = "Pushable";
						break;
					case 4:
						tag = "Hanger";
						break;
					case 5:
						tag = "Item";
						break;
					case 6:
						tag = "Enemy";
						break;
					case 7:
						tag = "Cat";
						break;
					case 8:
						tag = "Cat_Vase";
						break;
					case 9:
						tag = "Player";
						break;
					case 10:
						tag = "Boss";
						break;
					case 11:
						tag = "Prefab";
						break;
				}
				for (auto ent = mapEntity[tag].begin(); ent != mapEntity[tag].end(); ++ent)
				{
					if (ent->second->HaveComponent("RenderComponent"))
					{
							ent->second->GetComponent<RenderComponent>("RenderComponent")->
								Render(ent->second->GetComponent<TransformComponent>("TransformComponent"));
					}
				}
			}
			break;


		case 2:
			for (auto it = mapEntity["Layer_2"].begin(); it != mapEntity["Layer_2"].end(); ++it)
			{
				TransformComponent transf = *(it->second->GetComponent<TransformComponent>("TransformComponent"));
				transf.AddToPos( Point(Camera::pos.x * 0.5, Camera::pos.y * 0.5) );
				it->second->GetComponent<RenderComponent>("RenderComponent")->Render(&transf);
			}
			break;


		case 3:
			for (auto it = mapEntity["Layer_3"].begin(); it != mapEntity["Layer_3"].end(); ++it)
			{
				TransformComponent transf = *(it->second->GetComponent<TransformComponent>("TransformComponent"));
				transf.AddToPos( Point(Camera::pos.x * 0.75, /*0*/Camera::pos.y/* * 0.75*/) );
				it->second->GetComponent<RenderComponent>("RenderComponent")->Render(&transf);
			}
			break;
	}
}

/*************************************************************
 *
 * Update percorre o map de entidades e chama o update delas
 *
 *************************************************************/
void EntityManager::Update(float dt)
{
	for (auto it = mapEntity.begin(); it != mapEntity.end(); ++it)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			it2->second->Update(dt);
		}
	}
}

/*************************************************************
 *
 * bleh
 *
 *************************************************************/
void EntityManager::removeDeadEntities()
{

	for (auto it = mapEntity.begin(); it != mapEntity.end(); ++it)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			if(it2->second->toDelete)
			{
				//std::cout<<it2->second->GetName()<<std::endl;
				removeEntity(it2->second->id);
			}
		}
	}
}
