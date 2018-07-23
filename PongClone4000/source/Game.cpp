#include "Game.h"
#include "CollisionEngine.h"

Game::Game(MediaCache& mc, 
			const int numPlayers) : State(mc),
									font(mediaCache.getFont(60)),
									leftBat(std::make_unique<Bat>(1, mediaCache.getScrWidth(), mediaCache.getScrHeight())),
									rightBat(std::make_unique<Bat>(2, mediaCache.getScrWidth(), mediaCache.getScrHeight())),
									ball(std::make_unique<Ball>("files/ball.bmp", static_cast<int>(leftBat->getPosition().x) + leftBat->getWidth(), mediaCache.getScrHeight())),
									playerCount(numPlayers)
{
	net.h = mediaCache.getScrHeight() - 20;
	net.w = 2;
	net.x = mediaCache.centreX(net.w);
	net.y = mediaCache.centreY(net.h);
}

Game::~Game()
{

}

void Game::enter(Engine* )
{

}

void Game::handleEvents(SDL_Event &e, Engine* engine)
{
	keyPressed(e, engine);
}

void Game::update(const double dTime, Engine* )
{
	leftBat->move(mediaCache.getScrHeight(), dTime);
	rightBat->move(mediaCache.getScrHeight(), dTime);

	ball->move(mediaCache.getScrHeight(), mediaCache.getScrWidth(), leftBat->getBox(), rightBat->getBox(), dTime);
}

void Game::render()
{
	mediaCache.drawRectangle(net, { 0,0,0 });

	mediaCache.drawRectangle(leftBat->getBox(), leftBat->getColor());
	mediaCache.drawRectangle(rightBat->getBox(), rightBat->getColor());

	mediaCache.renderTexture(mediaCache.getImage(ball->getImage()), static_cast<int>(ball->getPosition().x), static_cast<int>(ball->getPosition().y));
}

void Game::exit(Engine* )
{

}

// ===============
// Class Functions
// ===============

void Game::keyPressed(SDL_Event &e, Engine*)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_w:
			{
				leftBat->setDirectionY(-1);
				if (!ball->isMoving())
				{
					ball->startMoving(1, -1);

				}
			}
				break;
			case SDLK_s:
			{
				leftBat->setDirectionY(1);
				if (!ball->isMoving())
				{
					ball->startMoving(1, 1);

				}
			}
				break;
		}

		if (playerCount == 2)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				rightBat->setDirectionY(-1);
				break;
			case SDLK_DOWN:
				rightBat->setDirectionY(1);
				break;
			}
		}
	}
	else if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_w:
			case SDLK_s:
				leftBat->setDirectionY(0);
				break;
		}

		if (playerCount == 2)
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_UP:
				case SDLK_DOWN:
					rightBat->setDirectionY(0);
					break;
			}
		}
	}
}