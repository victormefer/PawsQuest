#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <iostream>
#include <string>
#include <map>

class Entity;
class Component
{
public:
	Component();
	virtual ~Component();
	bool IsEnable();
	std::string GetName();
	void SetOwner(Entity*);
	Entity* GetOwner();
	void SetName(std::string);
	virtual void Update(float) = 0;
	void Enable();
	void Disable();
private:
	std::string name;
	Entity* owner;
	bool isEnable;
};

#endif
