#ifndef GAME_HPP
#define GAME_HPP

#include "SDL2_Common.h"
#include <memory>
#include <vector>
#include <string>

class Window;
class Renderer;
class PhysicsEngine;
class Timer;
class InputManager;
class RenderEngine;
class CollisionEngine;

class GameObject;
class Player;
class Score;

class Game {

public:

    ~Game();

    /* Alternative Singleton pattern using shared_ptr */
	static std::shared_ptr<Game> instance()
	{
		static std::shared_ptr<Game> game(new Game());
		return game;
	}

    void init();
    void setupGameState();
    void runGameLoop();

    std::shared_ptr <Renderer> getRenderer();

    static const int MAX_GAME_OBJECTS = 32;

    void registerGameObject(std::shared_ptr<GameObject> newGO);
    std::shared_ptr<GameObject> findGameObjectByName(std::string name);

    std::shared_ptr<Score> getScore();

private:
    Game();

    std::shared_ptr <Window> window;
    std::shared_ptr <Renderer> renderer;
    std::shared_ptr<Timer> timer;
    std::shared_ptr<InputManager> inputManager;
    std::shared_ptr<RenderEngine> renderEngine;
    std::shared_ptr<PhysicsEngine> physicsEngine;
    std::shared_ptr<CollisionEngine> collisionEngine;

    std::shared_ptr<Score> score; 

    std::vector<std::shared_ptr<GameObject>> gameObjects;

    // Window control 
    bool quit = false;

    void runGameLoopOnce();
    void draw();
    void update(float deltaTime);




};

#endif