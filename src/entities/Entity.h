#ifndef ENTITY_H_
#define ENTITY_H_

#include "../components/Component.h"
//#include "../messages/Message.h"
#include <iostream>
#include <map>
#include <string>

class Message;
class Entity
{
public:
	//enum TagType {PLAYER,ENEMY,GROUND,ITENS,OBJ};
	Entity();
	Entity(std::string);
	virtual ~Entity();
	unsigned int &GetId();
	std::string GetName();
	virtual void Update(float dt);
	void AddComponent(Component*);
	void RemoveComponent(std::string);
	void SendMessage(Message*);
	bool HaveComponent(std::string);
	void SetTag(std::string);
	void Delete();
	template<typename T>
	T* GetComponent(std::string name)
	{
		return dynamic_cast<T*>(mapComponents[name]);
	}
	unsigned int id;
	std::string name;
	std::string tag;
	bool toDelete;
	static unsigned int nextId;
	std::map<std::string,Component*> mapComponents;
};
#include "../messages/Message.h"

#endif
