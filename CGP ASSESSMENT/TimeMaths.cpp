#include "TimeMaths.h"

TimeMaths& TimeMaths::getInstance()
{
    static TimeMaths instance;
    return instance;
}

float TimeMaths::getDeltaTime() const
{
    return deltaTime * timeScale; 
}

float TimeMaths::setTimeScale(float NewtimeScale)
{
    timeScale = NewtimeScale;
    return timeScale; 
}

float TimeMaths::updateDeltaTime()
{
    deltaTime = (SDL_GetTicks() - (float)(previousFrameTicks)) / 1000;
    previousFrameTicks = SDL_GetTicks();
    return deltaTime;
}
TimeMaths::TimeMaths()
{
    updateDeltaTime();
}
