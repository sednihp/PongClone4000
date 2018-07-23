#ifndef ENGINE_H
#define ENGINE_H

#include "MediaCache.h"
#include "StateMachine.h"
#include <memory>

class Engine
{
	private: 
		bool running;
		double deltaTime;
		MediaCache mediaCache;
		std::unique_ptr<StateMachine> stateMachine;
		unsigned int randomNumber;

		void handleEvents();
		void update();
		void render();

	public:
		Engine();
		~Engine();

		void run();
		const bool isRunning() const { return running; }
		void stopRunning() { running = false; }

		void changeState(std::shared_ptr<State> newState);
		unsigned int getRandom(const int rangeMin, const int rangeMax);
};

#endif