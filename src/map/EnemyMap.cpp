#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>
#include "EnemyMap.h"
#include "../Timer.h"
#include "../managers/EntityManager.h"
#include "../components/TransformComponent.h"
#include "../components/RenderComponent.h"
#include "../components/MoveComponent.h"
#include "../components/BoxColliderComponent.h"
#include "../components/EnemyStateComponent.h"
#include "../components/IA_WalkRightLeftComponent.h"
#include "../components/IA_WalkUpDownComponent.h"
#include "../components/IA_WalkForwardComponent.h"
#include "../components/EnemyStateComponent.h"
#include "../components/BoxColliderComponent.h"
#include "../components/IA_FollowComponent.h"
#include "../components/HealthComponent.h"

using namespace std;

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
EnemyMap::EnemyMap(std::string file)
{
	numEnemy = 0;
	phase = 0;
	Load(file);
}

/*************************************************************
 *
 * Load
 *
 *************************************************************/
void EnemyMap::Load(std::string file)
{
	std::ifstream fin;
	fin.open(file, std::ios::in);
	char delimiter;

	fin >> numEnemy;
	fin >> delimiter;
	fin >> phase;
	fin >> delimiter;

	std::string name="", tag="", imgPath="", component="";
	int frameCount=1;
	float frameTime=0;
	float x=0, y=0, w=0, h=0, r=0, s1=1, s2=1;
	int first=0, last=0, up=0, down=0;
	float walkSpeed=0, runSpeed=0, acceleration=0;

	while(!fin.eof())
	{

		fin >> delimiter;
		fin >> name;
		fin >> tag;

		Entity* e = new Entity(name);

		TransformComponent* transformComponent = new TransformComponent(Rect(0,0,0,0),0,Point(0,0));
		RenderComponent* renderComponent = new RenderComponent("img/oi.png");
		MoveComponent* moveComponent = new MoveComponent(0,0,0);
		//BoxColliderComponent* boxcolliderComponent = new BoxColliderComponent(Rect(0,0,0,0),Point(1,1));
		IA_WalkRightLeftComponent* ia_walkrightleftComponent = new IA_WalkRightLeftComponent(0,0);
		IA_WalkUpDownComponent* ia_walkupdownComponent = new IA_WalkUpDownComponent(0,0);

		fin >> component;

		while(component != "*")
		{
			//case 0
			if(component == "EnemyStateComponent")
			{
				e->AddComponent(new EnemyStateComponent(ia));
			}
			//case 1
			if(component == "TransformComponent")
			{
				fin >> x;
				fin >> y;
				fin >> w;
				fin >> h;
				fin >> r;
				fin >> s1;
				fin >> s2;
				transformComponent->SetPosition(Rect(x,y,w,h));
				transformComponent->SetRotation(r);
				transformComponent->SetScale(Point(s1,s1));
				e->AddComponent(transformComponent);
			}
			//case 2
			else if(component == "RenderComponent")
			{
				fin >> imgPath;
				fin >> frameCount;
				fin >> frameTime;
				renderComponent->path = imgPath;
				renderComponent->SetFrameCount(frameCount);
				renderComponent->SetFrameTime(frameTime);
				renderComponent->Open(imgPath);
				e->AddComponent(renderComponent);
			}
			//case 3
			else if(component == "BoxColliderComponent")
			{
//				boxcolliderComponent->SetPosition
//				(
//					Rect
//					(
//						e->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x,
//						e->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
//						e->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
//						e->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h
//					),
//					Point
//					(
//						e->GetComponent<TransformComponent>("TransformComponent")->GetScale().getX(),
//						e->GetComponent<TransformComponent>("TransformComponent")->GetScale().getY()
//					)
//				);
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
//				e->AddComponent(boxcolliderComponent);
			}
			//case 4
			else if(component == "MoveComponent")
			{
				fin >> walkSpeed;
				fin >> runSpeed;
				fin >> acceleration;
				moveComponent->SetWalkSpeed(walkSpeed);
				moveComponent->SetRunSpeed(runSpeed);
				moveComponent->SetAcceletarion(acceleration);
				e->AddComponent(moveComponent);
			}
			//case 5
			else if(component == "IA_WalkRightLeftComponent")
			{
				fin >> first;
				fin >> last;
				ia_walkrightleftComponent->first = first;
				ia_walkrightleftComponent->last = last;
				ia = ia_walkrightleftComponent;
				e->AddComponent(ia_walkrightleftComponent);
			}
			//case 6
			else if(component == "IA_WalkUpDownComponent")
			{
				fin >> up;
				fin >> down;
				ia_walkupdownComponent->up = up;
				ia_walkupdownComponent->down = down;
				ia = ia_walkupdownComponent;
				e->AddComponent(ia_walkupdownComponent);
			}
			//case 7
			else if(component == "IA_FollowComponent")
			{
				float distance;
				fin >> distance;
				e->AddComponent(ia = new IA_FollowComponent(distance));
			}
			//case 8
			else if(component == "IA_WalkForwardComponent")
			{
				float distance;
				fin >> distance;
				e->AddComponent(ia = new IA_WalkForwardComponent(distance));
			}
			//case 9
			else if(component == "HealthComponent")
			{
				int maxHealth;
				fin >> maxHealth;
				e->AddComponent(new HealthComponent(maxHealth));
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
void EnemyMap::Render()
{

}

/*************************************************************
 *
 * GetNumEnemy
 *
 *************************************************************/
int EnemyMap::GetNumEnemy()
{
	return numEnemy;
}

/*************************************************************
 *
 * GetPhase
 *
 *************************************************************/
int EnemyMap::GetPhase()
{
	return phase;
}
