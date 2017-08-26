#include "../managers/EntityManager.h"
#include "../components/TransformComponent.h"
#include "../components/BoxColliderComponent.h"
#include "../components/RenderComponent.h"
#include "../components/BreakablePlatformComponent.h"
#include "ColliderMap.h"
#include "TileMap.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
ColliderMap::ColliderMap(std::string file)
{
	Load(file);
}

/*************************************************************
 *
 * Load
 *
 *************************************************************/
void ColliderMap::Load(std::string file)
{
	std::ifstream fin;
		fin.open(file, std::ios::in);
		char comma;

		fin >> mapHeight;
		fin >> comma;
		fin >> mapWidth;
		fin >> comma;

		for(int i=0; i<mapWidth; i++)
		{
			for(int j=0; j<mapHeight; j++)
			{
				int aux;
				fin >> aux;

				if(aux == 1)
				{
					Entity* e = new Entity("Ground");
					e->SetTag("Ground");
					e->AddComponent(new TransformComponent(Rect(
						j*64,i*64,64,64), 0, Point(1,1)));
					e->AddComponent(new BoxColliderComponent(
						Rect(j*64,i*64,64,64), Point(1,1)));
						// EntityManager::GetInstance().addEntity(e);
					TileMap::SetEntity(e, j, i, 0);
				}
				else if(aux == 2)
				{
					Entity* e = new Entity("Platform");
					e->SetTag("Platform");
					e->AddComponent(new TransformComponent(Rect(
						j*64,i*64,32,32), 0, Point(1,1)));
					e->AddComponent(new BoxColliderComponent(
						Rect(j*64,i*64,64,64), Point(1,1)));
						// EntityManager::GetInstance().addEntity(e);
					TileMap::SetEntity(e, j, i, 0);
				}
				else if(aux == 3)
				{
					Entity* e = new Entity("Edge");
					e->SetTag("Edge");
					e->AddComponent(new TransformComponent(Rect(
						j*64,i*64,64,64), 0, Point(1,1)));
					e->AddComponent(new BoxColliderComponent(
						Rect(j*64,i*64,64,64), Point(1,1)));
						// EntityManager::GetInstance().addEntity(e);
					TileMap::SetEntity(e, j, i, 0);
				}
				else if(aux == 4)
				{
					Entity* e = new Entity("Spike");
					e->SetTag("Ground");
					e->AddComponent(new TransformComponent(Rect(
							j*64,i*64,64,64), 0, Point(1,1)));
					e->AddComponent(new BoxColliderComponent(
							Rect(j*64,i*64,64,64), Point(1,1)));
					e->AddComponent(new RenderComponent("img/global/spike_64x64.png"));
					EntityManager::GetInstance().addEntity(e);
				}
				else if(aux == 5)
				{
					Entity* e = new Entity("Breakable");
					e->SetTag("Platform");
					e->AddComponent(new TransformComponent(Rect(
							j*64,i*64,32,32), 0, Point(1,1)));
					e->AddComponent(new BoxColliderComponent(
							Rect(j*64,i*64,64,64), Point(1,1)));
					e->AddComponent(new RenderComponent("img/fase_2/plataforma_quebravel_64x32.png"));
					e->AddComponent(new BreakablePlatformComponent());
					EntityManager::GetInstance().addEntity(e);
				}
				fin >> comma;
			}

		}
}

/*************************************************************
 *
 * GetWidth
 *
 *************************************************************/
int ColliderMap::GetWidth()
{
	return mapWidth;
}

/*************************************************************
 *
 * GetHeight
 *
 *************************************************************/
int ColliderMap::GetHeight()
{
	return mapHeight;
}


