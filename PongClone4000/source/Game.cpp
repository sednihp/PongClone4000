#include "Game.h"
#include "CollisionEngine.h"
#include <string>

Game::Game(MediaCache& mc, 
			const int numPlayers) : State(mc),
									font(mediaCache.getFont(60)), playerCount(numPlayers), p1(), p2(),
									leftBat(std::make_unique<Bat>(1, mediaCache.getScrWidth(), mediaCache.getScrHeight())),
									rightBat(std::make_unique<Bat>((numPlayers == 2) ? 2 : 3, mediaCache.getScrWidth(), mediaCache.getScrHeight())), 
									ball(std::make_unique<Ball>("files/ball.bmp", static_cast<int>(leftBat->getPosition().x) + leftBat->getWidth(), mediaCache.getScrHeight()))									
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
	leftBat->move(mediaCache.getScrHeight(), mediaCache.getScrWidth(), ball->getDirection(), ball->getPosition(), dTime);
	rightBat->move(mediaCache.getScrHeight(), mediaCache.getScrWidth(), ball->getDirection(), ball->getPosition(), dTime);

	int ballMove = ball->move(mediaCache.getScrHeight(), mediaCache.getScrWidth(), leftBat->getBox(), rightBat->getBox(), dTime);

	//leftBat=p1 has scored
	if (ballMove == 1)
	{
		ball->reset(static_cast<int>(rightBat->getPosition().x) - rightBat->getWidth(), mediaCache.getScrHeight());
		leftBat->reset(mediaCache.getScrHeight());
		p1.hasScored();
	}
	//rightBat=p2 has scored
	else if (ballMove == 2)
	{
		ball->reset(static_cast<int>(leftBat->getPosition().x) + leftBat->getWidth(), mediaCache.getScrHeight());
		rightBat->reset(mediaCache.getScrHeight());
		p2.hasScored();
	}
}

void Game::render()
{
	mediaCache.drawRectangle(net, { 0,0,0 });

	score = mediaCache.getText(std::to_string(p1.getScore()) + " " + std::to_string(p2.getScore()), font, mediaCache.getTextColor());
	score->setPosition(mediaCache.centreX(score->getW()), mediaCache.getScrHeight() - score->getH());
	mediaCache.renderTexture(score, score->getX(), score->getY());

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
		//always handle the player 1 controls, only handle player 2 if they're active
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