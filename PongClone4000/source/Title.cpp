#include "Title.h"
#include "Game.h"
#include "Engine.h"
#include "Controls.h"
#include "CollisionEngine.h"

Title::Title(MediaCache &mc) : State(mc), 
								font(mediaCache.getFont(80))
{
	SDL_Color c = mediaCache.getTextColor();
	title = mediaCache.getText("Another Pong Clone", font, c);
	title->setPosition(mediaCache.centreX(title->getW()), 10);

	menu.push_back(mediaCache.getText("Single Player", font, c));
	menu.push_back(mediaCache.getText("Multiplayer", font, c));
	menu.push_back(mediaCache.getText("Controls", font, c));
	menu.push_back(mediaCache.getText("Exit", font, c));

	for(size_t i=0; i<menu.size(); ++i)
	{
		menu[i]->setPosition(mediaCache.centreX(menu[i]->getW()), 2*title->getH() + i*menu[i]->getH());
	}
}

Title::~Title()
{
}

// ===============
// State functions
// ===============

void Title::enter(Engine*)
{
}

void Title::handleEvents(SDL_Event &e, Engine* engine)
{
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouseClicked(e, engine);
	}
}

void Title::update(const double, Engine*)
{
}

void Title::render()
{
	mediaCache.renderTexture(title, title->getX(), title->getY());

	for(auto &item : menu)
	{
		mediaCache.renderTexture(item, item->getX(), item->getY());
	}
}

void Title::exit(Engine* )
{

}

// ===============
// Class functions
// ===============

void Title::mouseClicked(SDL_Event&, Engine* engine)
{
	int x, y;
	if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
	{
		if (CollisionEngine::checkCollision(menu[0]->getBox(), x, y))
		{
			engine->changeState(std::make_shared<Game>(mediaCache, 1));
		}
		else if (CollisionEngine::checkCollision(menu[1]->getBox(), x, y))
		{
			engine->changeState(std::make_shared<Game>(mediaCache, 2));
		}
		else if (CollisionEngine::checkCollision(menu[2]->getBox(), x, y))
		{
			engine->changeState(std::make_shared<Controls>(mediaCache));
		}
		else if (CollisionEngine::checkCollision(menu[3]->getBox(), x, y))
		{
			engine->stopRunning();
		}
	}
}