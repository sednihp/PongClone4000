#include "Timer.h"
#include "SDL.h"

Timer::Timer() : startTicks(0), 
				pausedTicks(0),
				paused(false), 
				started(false)
{

}

Timer::~Timer()
{

}

void Timer::start()
{
	started = true;
	paused = false;

	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void Timer::stop()
{
	started = false;
	paused = false;

	startTicks = 0;
	pausedTicks = 0;
}

void Timer::restart()
{
	start();
}

void Timer::pause()
{
	if (started && !paused)
	{
		paused = true;

		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void Timer::unpause()
{
	if (started && paused)
	{
		paused = false;

		startTicks = SDL_GetTicks() - pausedTicks;

		pausedTicks = 0;
	}
}

unsigned int Timer::getTicks()
{
	unsigned int time = 0;

	if (started)
	{
		if (paused)
		{
			time = pausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - startTicks;
		}
	}

	return time;
}

double Timer::getSeconds()
{
	return getTicks() / 1000.0;
}

bool Timer::isStarted()
{
	return started;
}

bool Timer::isPaused()
{
	return paused && started;
}