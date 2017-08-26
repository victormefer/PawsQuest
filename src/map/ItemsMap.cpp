#include "ItemsMap.h"
#include "../managers/EntityManager.h"
#include "../components/TransformComponent.h"
#include "../components/RenderComponent.h"
#include "../components/BoxColliderComponent.h"
#include "../components/HidranteTimerComponent.h"
#include "../components/AttachableComponent.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
ItemsMap::ItemsMap(std::string file)
{
	numItems = 0;
	Load(file);
}

/*************************************************************
 *
 * Load
 *
 *************************************************************/
void ItemsMap::Load(std::string file)
{
	std::ifstream fin;
	fin.open(file, std::ios::in);
	char delimiter;

	fin >> numItems;
	fin >> delimiter;
	fin >> phase;
	fin >> delimiter;

	while(!fin.eof())
	{
		std::string name,
		tag,
		imgPath,
		component;
		int frameCount;
		float frameTime;

		fin >> delimiter;
		fin >> name;
		fin >> tag;

		Entity* e = new Entity(name);

		fin >> component;

		while(component != "*")
		{
			//case 0
			if(component == "TransformComponent")
			{
				int x, y, w,
				h, r, s1, s2;
				fin >> x;
				fin >> y;
				fin >> w;
				fin >> h;
				fin >> r;
				fin >> s1;
				fin >> s2;
				e->AddComponent(new TransformComponent
								(Rect(x,y, w, h),
								 (float)r,
								 Point(s1,s2)));
			}
			//case 1
			else if(component == "RenderComponent")
			{
				fin >> imgPath;
				fin >> frameCount;
				fin >> frameTime;
				e->AddComponent(new RenderComponent(imgPath,frameCount,frameTime));
			}
			//case 2
			else if(component == "BoxColliderComponent")
			{
				e->AddComponent(new BoxColliderComponent(
				Rect
				(
					e->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x,
					e->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
					e->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
					e->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h
				),
				Point
				(
					 e->GetComponent<TransformComponent>("TransformComponent")->GetScale().getX(),
					 e->GetComponent<TransformComponent>("TransformComponent")->GetScale().getY()
				)
				)
				);
			}
			//case 3
			else if(component == "HidranteTimerComponent")
			{
				e->AddComponent(new HidranteTimerComponent());
			}
			//case 4
			else if(component == "AttachableComponent.h")
			{
				e->AddComponent(new AttachableComponent());
			}
			//default
			else
			{

			}
			fin >> component;
		}
		e->SetTag(tag);
		EntityManager::GetInstance().addEntity(e);
	}

}

/*************************************************************
 *
 * Render
 *
 *************************************************************/
void ItemsMap::Render()
{

}

/*************************************************************
 *
 * GetNumItems
 *
 *************************************************************/
int ItemsMap::GetNumItems()
{
	return numItems;
}

/*************************************************************
 *
 * GetPhase
 *
 *************************************************************/
int ItemsMap::GetPhase()
{
	return phase;
}









