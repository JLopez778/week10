#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>

class GameObject;

class Component
{
public:
	Component();
	Component(std::shared_ptr<GameObject> newGameObject);
	~Component();

	void setGameObject(std::shared_ptr<GameObject> newGameObject);
	std::shared_ptr<GameObject> getGameObject();

protected:
	std::shared_ptr<GameObject> gameObject;
};

#endif

