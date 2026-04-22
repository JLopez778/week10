#include "InputManager.hpp"
#include "Vector3f.hpp"

InputManager::InputManager()
{
    keyStates = nullptr;
    quit = false;
    fire = false;
    mousePosition = nullptr;
}

void InputManager::init()
{
    // Track Keystates array
    keyStates = SDL_GetKeyboardState(NULL);

    mousePosition.reset(new Vector3f(0.0f,0.0f,0.0f));
}

InputManager::~InputManager()
{
    keyStates = nullptr;
}

bool InputManager::isWindowClosedEvent()
{
    return quit;
}

float InputManager::getHorizontalInput()
{
    if (keyStates[SDL_SCANCODE_RIGHT])
        return 1.0f;
    else
    {
        if (keyStates[SDL_SCANCODE_LEFT])
            return -1.0f;
        else
            return 0.0f;
    }
}

float InputManager::getVerticalInput()
{
    if (keyStates[SDL_SCANCODE_UP])
        return -1.0f;
    else
    {
        if (keyStates[SDL_SCANCODE_DOWN])
            return 1.0f;
        else
            return 0.0f;
    }
}

void InputManager::update()
{
    if (SDL_PollEvent(&event))  // test for events
    {
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
            break;
        }
    }

    int mouseX;
    int mouseY;

    Uint32 button = SDL_GetMouseState(&mouseX, &mouseY);

    this->mousePosition->setX(mouseX);
    this->mousePosition->setY(mouseY);

    if (button) 
    {
        if(button == SDL_BUTTON(SDL_BUTTON_RIGHT))
            fire = true;
        else
            fire = false;
    }
}

std::shared_ptr<Vector3f> InputManager::getMousePosition()
{
    return this->mousePosition;
}

bool InputManager::getFire()
{
    return fire;
}
