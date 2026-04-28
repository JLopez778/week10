#ifndef GAMEOBJECTFACTORY_HPP
#define GAMEOBJECTFACTORY_HPP

#include <memory>
#include <string>

class Background;
class Player;
class Renderer; 
class NPC;
class Bullet;

class GameObjectFactory
{
private:
	// Singleton - private constructor!
	GameObjectFactory();
	void init();

	static std::shared_ptr<GameObjectFactory> gof;

    std::shared_ptr<Renderer> renderer;

public:
	static std::shared_ptr<GameObjectFactory> instance();
	
    ~GameObjectFactory();

    std::shared_ptr<Background> createBackground();
    std::shared_ptr<Player> createPlayer();
    std::shared_ptr<NPC> createNPC(std::string path);
	std::shared_ptr<Bullet> createBullet();

	const int MAX_BULLETS = 32;
};

#endif