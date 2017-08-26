#include "ObjectMap.h"
#include "../managers/EntityManager.h"
#include "../components/TransformComponent.h"
#include "../components/RenderComponent.h"
#include "../components/BoxColliderComponent.h"
#include "../components/BreakablePlatformComponent.h"
#include "../components/PlatformComponent.h"
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
ObjectMap::ObjectMap(std::string file)
{
	Load(file);
}

/*************************************************************
 *
 * Load
 *
 *************************************************************/
void ObjectMap::Load(std::string file)
{
	std::ifstream fin;
	fin.open(file, std::ios::in);

	char delimiter;

	fin >> numObjects;
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
		//fin >> delimiter;

		Entity* e = new Entity(name);

		fin >> component;

		while(component != "*")
		{
			//case 0
			if(component == "TransformComponent")
			{
				float x, y, w,
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
				e->AddComponent(new RenderComponent(imgPath, frameCount, frameTime));
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
			else if(component == "PlatformComponent")
			{
				int range = 0;
				fin >> range;
				e->AddComponent(new PlatformComponent(e->GetComponent
						<TransformComponent>("TransformComponent"),
						range));
			}
			//case 4
			else if(component == "BreakablePlatformComponent")
			{
				e->AddComponent(new BreakablePlatformComponent());
			}
			//case 5
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
		//mapObject[e->GetId()] = e;
		EntityManager::GetInstance().addEntity(e);
	}
}
/*
void ObjectMap::Update(float dt)
{
	for (std::map<int,Entity*>::iterator it = mapObject.begin();
				it != mapObject.end(); ++it)
	{
		it->second->Update(dt);
	}
}

void ObjectMap::RenderLayer(int layer, int cameraX, int cameraY)
{
	for (std::map<int,Entity*>::iterator it = mapObject.begin();
				it != mapObject.end(); ++it)
		{
			switch(layer)
			{
				case 0:
					if (it->second->tag == "Layer_0")
					{
						TransformComponent transf = *(it->second->GetComponent<TransformComponent>("TransformComponent"));
						transf.AddToPos( Point(cameraX * 0.5, cameraY * 0.5) );
						it->second->GetComponent<RenderComponent>("RenderComponent")->Render(&transf);
					}
					break;
				case 1:
					if (it->second->tag != "Layer_0" && it->second->tag != "Layer_2" && it->second->tag != "Layer_3")
					{
						it->second->GetComponent<RenderComponent>("RenderComponent")->Render(
							it->second->GetComponent<TransformComponent>("TransformComponent"));
					}
					break;
				case 2:
					if (it->second->tag == "Layer_2")
					{
						TransformComponent transf = *(it->second->GetComponent<TransformComponent>("TransformComponent"));
						transf.AddToPos( Point(-cameraX * 0.75, -cameraY * 0.75) );
						it->second->GetComponent<RenderComponent>("RenderComponent")->Render(&transf);
					}
					break;
				case 3:
					if (it->second->tag == "Layer_3")
					{
						TransformComponent transf = *(it->second->GetComponent<TransformComponent>("TransformComponent"));
						transf.AddToPos( Point(-cameraX * 0.5, -cameraY * 0.5) );
						it->second->GetComponent<RenderComponent>("RenderComponent")->Render(&transf);
					}
					break;
			}
		}
}


void ObjectMap::RenderBelow(int cameraX, int cameraY)
{
	RenderLayer(3, cameraX, cameraY);
	RenderLayer(2, cameraX, cameraY);
	RenderLayer(1, cameraX, cameraY);
}*/

/*************************************************************
 *
 * GetnumObjects
 *
 *************************************************************/
int ObjectMap::GetnumObjects()
{
	return numObjects;
}

/*************************************************************
 *
 * GetPhase
 *
 *************************************************************/
int ObjectMap::GetPhase()
{
	return phase;
}








