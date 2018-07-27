#include "Engine.h"

int main(int, char**)
{
	Engine engine;

	while(engine.isRunning())
	{
		engine.run();
	}

    return 0;
}