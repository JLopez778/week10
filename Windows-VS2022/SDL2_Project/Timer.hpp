#ifndef TIMER_HPP
#define TIMER_HPP

#include <memory>

class Timer
{
private:
	// Singlton - private constructor!
	Timer();
	void init();
	float deltaTime;
	bool restart;

	// Timing variables
	unsigned int currentTimeIndex;
	unsigned int prevTimeIndex;
	unsigned int timeDelta;
	

	static std::shared_ptr<Timer> timer;

public:
	/* Alternative Singlton pattern using shared_ptr */
	static std::shared_ptr<Timer> instance();

	void update();
	float getDeltaTime();
};

#endif

