#include "Game.hpp"
#include "SDL2_Common.h"

#include "Window.hpp" 
#include "Renderer.hpp"
 
#include "Timer.hpp"
#include "InputManager.hpp"

#include "RenderEngine.hpp"
#include "PhysicsEngine.hpp"
#include "CollisionEngine.hpp"

#include "Sprite.hpp"
#include "PhysicsComponent.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "Vector3f.hpp"

#include "GameObject.hpp"
#include "GameObjectFactory.hpp"
#include "Background.hpp"
#include "Player.hpp"
#include "NPC.hpp"

#include "score.hpp"

#include <iostream>

Game::Game()
{
    window = nullptr;
    renderer = nullptr;
    physicsEngine = nullptr;
    renderEngine = nullptr;
    inputManager = nullptr;
}

Game::~Game()
{
    window.reset();
    window = nullptr;

    renderer.reset();
    renderer = nullptr;

    renderEngine.reset();
    renderEngine = nullptr;

    physicsEngine.reset();
    physicsEngine = nullptr;

    std::vector<std::shared_ptr<GameObject>>::iterator itt;
    for(itt = gameObjects.begin(); itt != gameObjects.end(); ++itt)
    {
        (*itt).reset(); // call reset on the shared pointer!
    }

    //Shutdown SDL - clear up resources etc. 
    SDL_Quit();
}

void Game::init()
{
    // SDL allows us to choose which SDL components are  
    // going to be initialised. 
    // Lets go for everything for now!
    SDL_Init(SDL_INIT_EVERYTHING);

    window = std::shared_ptr<Window>(new Window());
    window->init();

    renderer = std::shared_ptr<Renderer>(new Renderer());
    renderer->init(window->getWindow());

    gameObjects.resize(MAX_GAME_OBJECTS);

    renderEngine = std::shared_ptr<RenderEngine>(new RenderEngine());
    renderEngine->init(MAX_GAME_OBJECTS, renderer);

    timer = Timer::instance();
    inputManager = InputManager::instance();

    GameObjectFactory::instance();

    physicsEngine = std::shared_ptr<PhysicsEngine>(new PhysicsEngine());
    physicsEngine->init(MAX_GAME_OBJECTS);

    collisionEngine = std::shared_ptr<CollisionEngine>(new CollisionEngine());
    collisionEngine->init(MAX_GAME_OBJECTS);

    std::shared_ptr<Background> background = GameObjectFactory::instance()->createBackground();

    std::shared_ptr<Player> player = GameObjectFactory::instance()->createPlayer();

    score.reset(new Score());

    std::shared_ptr<NPC> npc = GameObjectFactory::instance()->createNPC("assets/images/Enemy.png");
    std::shared_ptr<NPC> npc2 = GameObjectFactory::instance()->createNPC("assets/images/Enemy2.png");
    std::shared_ptr<NPC> npc3 = GameObjectFactory::instance()->createNPC("assets/images/Enemy3.png");
    //std::shared_ptr<NPC> npc = GameObjectFactory::instance()->createNPC("assets/images/playerShip.png");
}

void Game::setupGameState()
{

}

void Game::runGameLoop()
{
    // for last_time. 
    timer->update();
    inputManager->update();

    // Game loop
    while(!quit) // while quit is not true
    { 
        // update systems
        timer->update();

       
        runGameLoopOnce();
    }
}

void Game::runGameLoopOnce()
{
    float deltaTime = timer->getDeltaTime();

    // process inputs
    inputManager->update();
    quit = inputManager->isWindowClosedEvent();

    // update game state
    update(deltaTime);

    // draw
    draw();

}

void Game::draw()
{
    // Draw ...

    // 1. Clear the screen
    renderer->clear();

    // 2. Draw the scene
    renderEngine->render();

    // 3. Present the current frame to the screen
    renderer->present();
}

void Game::update(float deltaTime)
{
   physicsEngine->update(deltaTime);

   collisionEngine->check();

   std::shared_ptr<GameObject> gameObject;

    std::vector<std::shared_ptr<GameObject>>::iterator itt;
    for(itt = gameObjects.begin(); itt != gameObjects.end(); ++itt)
    {
        gameObject = *itt;
        
        if(gameObject == nullptr)
            continue;
        else
            gameObject->update();
    }

}


std::shared_ptr<Renderer> Game::getRenderer()
{
    return renderer;
}

void Game::registerGameObject(std::shared_ptr<GameObject> newGO)
{
    bool added = false;
    std::vector<std::shared_ptr<GameObject>>::iterator itt;
    for(itt = gameObjects.begin(); itt != gameObjects.end(); ++itt)
    {
        if(*itt == nullptr)
        {
            *itt = newGO;
            added = true;
            break;
        }
    }

    if(added == false) 
    {
        std::cout << "Ran out of pre-allocated game objects" << std::endl;
        // No point in registering the rest of the components it would
        // just crash
        return; // need better error handling!
    }

    std::shared_ptr<Sprite> sprite = newGO->getSprite();

    if(sprite != nullptr)
        renderEngine->addSprite(sprite);

    std::shared_ptr<PhysicsComponent> phys = newGO->getPhysicsComponent();

    if(phys != nullptr)
        physicsEngine->addPhysicsComponent(phys);

    std::shared_ptr<Collider> col = newGO->getCollisionComponent();

    if(phys != nullptr) 
        collisionEngine->addCollider(col);
}

// Finds first thing with that name!
std::shared_ptr<GameObject> Game::findGameObjectByName(std::string name)
{
    std::shared_ptr<GameObject> gameObject;
    std::shared_ptr<GameObject> found = nullptr;

    std::vector<std::shared_ptr<GameObject>>::iterator itt;
    for(itt = gameObjects.begin(); itt != gameObjects.end(); ++itt)
    {
        gameObject = *itt;

        if(gameObject == nullptr)
            continue;
        
        if(gameObject->getName() == name) 
        {
            found = gameObject;
            break;
        }
    }

    return found;
}


std::shared_ptr<Score> Game::getScore()
{
    return score;
}