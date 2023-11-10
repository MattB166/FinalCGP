#pragma once
#include "SDL.h"
class TimeMaths
{

public: 
	static TimeMaths& getInstance();

	float getDeltaTime() const; 
	float setTimeScale(float timeScale);


private:
	TimeMaths();
	float updateDeltaTime();
	float deltaTime;
	float timeScale = 1; 
	Uint32 previousFrameTicks;
	
};

