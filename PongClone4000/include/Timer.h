#ifndef TIMER_H
#define TIMER_H

class Timer
{
	private:
		unsigned int startTicks;
		unsigned int pausedTicks;
		bool paused;
		bool started;

	public:
		Timer();
		~Timer();

		void start();
		void stop();
		void restart();
		void pause();
		void unpause();

		unsigned int getTicks();
		double getSeconds();

		bool isStarted();
		bool isPaused();
};

#endif