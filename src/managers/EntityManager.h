#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include <map>
#include <string>

#include "../entities/Entity.h"

class EntityManager {
	public:
		EntityManager();
		static EntityManager& GetInstance();
		static Entity* GetEntityById(int);
		static Entity* GetEntityByName(std::string);
		static void addEntity(Entity* entity);
		static void removeDeadEntities();
		static void removeEntity(int id);
		static int Size();
		static void Update(float);
		static void RenderLayer(int layer);
		static std::map<std::string, std::map<int,Entity*> > mapEntity;
	private:
		static EntityManager* instance;
};

#endif
