#ifndef GAMEOBJECTFACTORY_HPP
#define GAMEOBJECTFACTORY_HPP

#include <memory>

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

    std::shared_ptr<Renderer> renderer;

public:
	/* Alternative Singleton pattern using shared_ptr */
	static std::shared_ptr<GameObjectFactory> instance()
	{
		static std::shared_ptr<GameObjectFactory> gof(new GameObjectFactory());
        gof->init();
		return gof;
	}

    ~GameObjectFactory();

    std::shared_ptr<Background> createBackground();
    std::shared_ptr<Player> createPlayer();
    std::shared_ptr<NPC> createNPC();
	std::shared_ptr<Bullet> createBullet();

	const int MAX_BULLETS = 32;
};

#endif