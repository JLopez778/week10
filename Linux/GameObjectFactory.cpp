#include "GameObjectFactory.hpp"

#include "Background.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "Bullet.hpp"
 
// Components 
#include "Sprite.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Vector3f.hpp"
#include "PhysicsComponent.hpp"
#include "Collider.hpp"

#include "Window.hpp"
#include "Game.hpp"
#include "Renderer.hpp"

#include "SDL2_Common.h"


GameObjectFactory::GameObjectFactory()
{
    renderer = nullptr;
}

void GameObjectFactory::init()
{
    renderer = Game::instance()->getRenderer();
}

GameObjectFactory::~GameObjectFactory()
{
    renderer.reset();
}

std::shared_ptr<Background> GameObjectFactory::createBackground()
{
    std::shared_ptr<Background> background = std::shared_ptr<Background>(new Background());

    // Sprite
    std::shared_ptr<Sprite> backgroundSprite = std::shared_ptr<Sprite>(new Sprite());

    // Texture
    std::shared_ptr<Texture> backgroundTexture = std::shared_ptr<Texture>(new Texture());
    
    // This mess loads a texture .. make this better. 
    SDL_Surface* temp = IMG_Load("assets/images/background.png");

    backgroundTexture->setTexture(SDL_CreateTextureFromSurface(renderer->getRenderer(), temp));

    SDL_FreeSurface(temp);
    temp = nullptr;

    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    
    SDL_QueryTexture(backgroundTexture->getTexture(), NULL, NULL, &source.w, &source.h);
    backgroundTexture->setSourceRectangle(source);

    backgroundSprite->setTexture(backgroundTexture);

    // Setup two way relationship
    backgroundSprite->setGameObject(background);
    background->setSprite(backgroundSprite);

    // Add to engine - registerGameObject()?
    // renderEngine->addSprite(backgroundSprite);

    // Transform
    std::shared_ptr<Transform> backgroundTransform = std::shared_ptr<Transform>(new Transform());
    backgroundTransform->setAngle(0.0f);
    backgroundTransform->setPosition(std::shared_ptr<Vector3f>(new Vector3f(0.0f,0.0f,0.0f)));  
    
    float bgScaleX = Window::WINDOW_WIDTH/(float)source.w;
    float bgScaleY = Window::WINDOW_HEIGHT/(float)source.h;

    backgroundTransform->setScale(std::shared_ptr<Vector3f>(new Vector3f(bgScaleX,bgScaleY,0.0f))); 

    background->setTransform(backgroundTransform);

    background->enable();

    return background;
}

std::shared_ptr<Player> GameObjectFactory::createPlayer()
{
    std::shared_ptr<Player> player = std::shared_ptr<Player>(new Player());
    player->init(MAX_BULLETS);

    // Sprite
    std::shared_ptr<Sprite> playerSprite = std::shared_ptr<Sprite>(new Sprite());

    // Texture
    std::shared_ptr<Texture> playerTexture = std::shared_ptr<Texture>(new Texture());
    
    // This mess loads a texture .. make this better. 
    SDL_Surface* temp = IMG_Load("assets/images/playerShip.png");

    playerTexture->setTexture(SDL_CreateTextureFromSurface(renderer->getRenderer(), temp));

    SDL_FreeSurface(temp);
    temp = nullptr;

    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    
    SDL_QueryTexture(playerTexture->getTexture(), NULL, NULL, &source.w, &source.h);
    playerTexture->setSourceRectangle(source);

    playerSprite->setTexture(playerTexture);
    
    // Setup two way relationship
    player->setSprite(playerSprite);
    playerSprite->setGameObject(player);

    // Transform
    std::shared_ptr<Transform> playerTransform = std::shared_ptr<Transform>(new Transform());
    playerTransform->setAngle(0.0f);
    playerTransform->setPosition(std::shared_ptr<Vector3f>(new Vector3f(100.0f,100.0f,0.0f)));  

    playerTransform->setScale(std::shared_ptr<Vector3f>(new Vector3f(1.0f,1.0f,0.0f))); 

    player->setTransform(playerTransform);

    // Physics
    std::shared_ptr<PhysicsComponent> physics = std::shared_ptr<PhysicsComponent>(new PhysicsComponent());
    physics->setVelocity(std::shared_ptr<Vector3f>(new Vector3f(1.0f,1.0f,0.0f)));
    
    // setup two way relationship
    physics->setGameObject(player);
    player->setPhysicsComponent(physics);

    // Collider
    std::shared_ptr<Collider> collider = std::shared_ptr<Collider>(new Collider());
    collider->setRadius(playerTexture->getSourceRectangle().w/2.0f);
    collider->setResolution(true);

    // setup two way relationship
    collider->setGameObject(player);
    player->setCollisionComponent(collider);

    player->enable();

    return player;
}

std::shared_ptr<NPC> GameObjectFactory::createNPC()
{
    std::shared_ptr<NPC> npc = std::shared_ptr<NPC>(new NPC());

    // Sprite
    std::shared_ptr<Sprite> npcSprite = std::shared_ptr<Sprite>(new Sprite());

    // Texture
    std::shared_ptr<Texture> npcTexture = std::shared_ptr<Texture>(new Texture());
    
    // This mess loads a texture .. make this better. 
    SDL_Surface* temp = IMG_Load("assets/images/playerShip.png");

    npcTexture->setTexture(SDL_CreateTextureFromSurface(renderer->getRenderer(), temp));

    SDL_FreeSurface(temp);
    temp = nullptr;

    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    
    SDL_QueryTexture(npcTexture->getTexture(), NULL, NULL, &source.w, &source.h);
    npcTexture->setSourceRectangle(source);

    npcSprite->setTexture(npcTexture);
    
    // Setup two way relationship
    npc->setSprite(npcSprite);
    npcSprite->setGameObject(npc);

    // Transform
    std::shared_ptr<Transform> npcTransform = std::shared_ptr<Transform>(new Transform());
    npcTransform->setAngle(0.0f);

    std::shared_ptr<Vector3f> offscreen = std::shared_ptr<Vector3f>(new Vector3f(0.0f,0.0f,0.0f));

    float w = Window::WINDOW_WIDTH;
    float h = Window::WINDOW_HEIGHT;

    // Make this a random offscreen position
    offscreen->setX(w+10.0f);
    offscreen->setY(h/2.0f);
    
    npcTransform->setPosition(offscreen);  

    npcTransform->setScale(std::shared_ptr<Vector3f>(new Vector3f(1.0f,1.0f,0.0f))); 

    npc->setTransform(npcTransform);

    // Physics
    std::shared_ptr<PhysicsComponent> physics = std::shared_ptr<PhysicsComponent>(new PhysicsComponent());
    physics->setVelocity(std::shared_ptr<Vector3f>(new Vector3f(1.0f,1.0f,0.0f)));
    
    // setup two way relationship
    physics->setGameObject(npc);
    npc->setPhysicsComponent(physics);

    // Collider
    std::shared_ptr<Collider> collider = std::shared_ptr<Collider>(new Collider());
    collider->setRadius(npcTexture->getSourceRectangle().w/2.0f);
    collider->setResolution(true);

    // setup two way relationship
    collider->setGameObject(npc);
    npc->setCollisionComponent(collider);

    npc->enable();

    return npc;
}

std::shared_ptr<Bullet> GameObjectFactory::createBullet()
{
     std::shared_ptr<Bullet> bullet = std::shared_ptr<Bullet>(new Bullet());

    // Sprite
    std::shared_ptr<Sprite> bulletSprite = std::shared_ptr<Sprite>(new Sprite());

    // Texture
    std::shared_ptr<Texture> bulletTexture = std::shared_ptr<Texture>(new Texture());
    
    // This mess loads a texture .. make this better. 
    SDL_Surface* temp = IMG_Load("assets/images/playerShip.png");

    bulletTexture->setTexture(SDL_CreateTextureFromSurface(renderer->getRenderer(), temp));

    SDL_FreeSurface(temp);
    temp = nullptr;

    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    
    SDL_QueryTexture(bulletTexture->getTexture(), NULL, NULL, &source.w, &source.h);
    bulletTexture->setSourceRectangle(source);

    bulletSprite->setTexture(bulletTexture);
    
    // Setup two way relationship
    bullet->setSprite(bulletSprite);
    bulletSprite->setGameObject(bullet);

    // Transform
    std::shared_ptr<Transform> bulletTransform = std::shared_ptr<Transform>(new Transform());
    bulletTransform->setAngle(0.0f);

    std::shared_ptr<Vector3f> offscreen = std::shared_ptr<Vector3f>(new Vector3f(0.0f,0.0f,0.0f));

    float w = Window::WINDOW_WIDTH;
    float h = Window::WINDOW_HEIGHT;

    // Make this a random offscreen position
    offscreen->setX(w+10.0f);
    offscreen->setY(h/2.0f);
    
    bulletTransform->setPosition(offscreen);  

    bulletTransform->setScale(std::shared_ptr<Vector3f>(new Vector3f(1.0f,1.0f,0.0f))); 

    bullet->setTransform(bulletTransform);

    // Physics
    std::shared_ptr<PhysicsComponent> physics = std::shared_ptr<PhysicsComponent>(new PhysicsComponent());
    physics->setVelocity(std::shared_ptr<Vector3f>(new Vector3f(1.0f,1.0f,0.0f)));
    
    // setup two way relationship
    physics->setGameObject(bullet);
    bullet->setPhysicsComponent(physics);

    // Collider
    std::shared_ptr<Collider> collider = std::shared_ptr<Collider>(new Collider());
    collider->setRadius(bulletTexture->getSourceRectangle().w/2.0f);
    collider->setResolution(true);

    // setup two way relationship
    collider->setGameObject(bullet);
    bullet->setCollisionComponent(collider);

    bullet->enable();

    return bullet;
}
