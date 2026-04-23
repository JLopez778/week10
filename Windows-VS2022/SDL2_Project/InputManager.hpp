#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <memory>

#include "SDL2_Common.h"

class Vector3f;

class InputManager
{
private:
	// Singleton - private constructor!
	InputManager();
	void init();
	
	SDL_Event event;
	bool quit;
	const Uint8* keyStates;
	std::shared_ptr<Vector3f> mousePosition;
	bool fire;

	static std::shared_ptr<InputManager> inputManager;

public:
	
	static std::shared_ptr<InputManager> instance();

	~InputManager();
	
	void update();
	bool isWindowClosedEvent();
	float getHorizontalInput();
	float getVerticalInput();
	
	std::shared_ptr<Vector3f> getMousePosition();
	bool getFire();

};
#endif

