#include "Controls.h"
#include "CollisionEngine.h"
#include "Title.h"
#include "Engine.h"

Controls::Controls(MediaCache& mc) : State(mc),
									font(mediaCache.getFont(60))
{
	SDL_Color c = mediaCache.getTextColor();
	title = mediaCache.getText("Controls", font, c);
	title->setPosition(mediaCache.centreX(title->getW()), 10);

	controls.push_back(mediaCache.getText("Player 1:", font, c));
	controls.push_back(mediaCache.getText("W and S", font, c));
	controls.push_back(mediaCache.getText("======", font, c));
	controls.push_back(mediaCache.getText("Player 2:", font, c));
	controls.push_back(mediaCache.getText("Up and Down arrows", font, c));

	for (size_t i = 0; i < controls.size(); i++)
	{
		controls[i]->setPosition(mediaCache.centreX(controls[i]->getW()), 2 * title->getH() + i * controls[0]->getH());
	}

	menu = mediaCache.getText("Main Menu", font, c);
	menu->setPosition(mediaCache.centreX(title->getW()), mediaCache.getScrHeight() - menu->getH() - 10);
}

Controls::~Controls()
{
}

void Controls::enter(Engine* )
{

}

void Controls::handleEvents(SDL_Event &e, Engine* engine)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouseClicked(e, engine);
	}
}

void Controls::update(const double , Engine* )
{

}

void Controls::render()
{
	mediaCache.renderTexture(title, title->getX(), title->getY());

	for(const auto& c: controls)
	{
		mediaCache.renderTexture(c, c->getX(), c->getY());
	}

	mediaCache.renderTexture(menu, menu->getX(), menu->getY());
}

void Controls::exit(Engine* )
{

}

// ===============
// Class functions
// ===============

void Controls::mouseClicked(SDL_Event &, Engine* engine)
{
	int x, y;
	if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
	{
		if (CollisionEngine::checkCollision(menu->getBox(), x, y))
		{
			engine->changeState(std::make_shared<Title>(mediaCache));
		}
	}
}