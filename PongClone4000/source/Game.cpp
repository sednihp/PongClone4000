#include "Game.h"
#include "CollisionEngine.h"
#include <string>
#include "Engine.h"
#include "Title.h"

Game::Game(MediaCache& mc, const int numPlayers) : State(mc),
													font(mediaCache.getFont(60)), smallFont(mediaCache.getFont(40)), 
													humanPlayerCount(numPlayers), p1(), p2(), winningPlayer(0), paused(false),
													leftBat(std::make_unique<Bat>(1, mediaCache.getScrWidth(), mediaCache.getScrHeight())),
													rightBat(std::make_unique<Bat>((numPlayers == 2) ? 2 : 3, mediaCache.getScrWidth(), mediaCache.getScrHeight())), 
													ball(std::make_unique<Ball>("files/ball.bmp", static_cast<int>(leftBat->getPosition().x) + leftBat->getWidth(), mediaCache.getScrHeight())),
													winningTex(nullptr)
{
	net.h = mediaCache.getScrHeight() - 20;
	net.w = 2;
	net.x = mediaCache.centreX(net.w);
	net.y = mediaCache.centreY(net.h);

	generateTextures();
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
	mouseClicked(e, engine);
}

void Game::update(const double dTime, Engine* )
{
	if (winningPlayer == 0 && !paused)
	{
		moveBats(dTime);

		checkIfBallMoving();

		checkIfGoalScored(moveBall(dTime));

		checkforWinner();
	}
}

void Game::render()
{
	mediaCache.drawRectangle(net, { 0,0,0 });
	mediaCache.renderTexture(p1Tex, p1Tex->getX(), p1Tex->getY());
	mediaCache.renderTexture(p2Tex, p2Tex->getX(), p2Tex->getY());
	mediaCache.renderTexture(pauseTex, pauseTex->getX(), pauseTex->getY());
	mediaCache.renderTexture(menuTex, menuTex->getX(), menuTex->getY());

	createScoreTex();
	mediaCache.renderTexture(scoreTex, scoreTex->getX(), scoreTex->getY());

	mediaCache.drawRectangle(leftBat->getBox(), leftBat->getColor());
	mediaCache.drawRectangle(rightBat->getBox(), rightBat->getColor());

	mediaCache.renderTexture(mediaCache.getImage(ball->getImage()), static_cast<int>(ball->getPosition().x), static_cast<int>(ball->getPosition().y));

	if (winningPlayer > 0)
	{
		renderWinningText();
	}

	if (paused)
	{
		mediaCache.renderTexture(pausedMsgTex, pausedMsgTex->getX(), pausedMsgTex->getY());
	}
}

void Game::exit(Engine* )
{

}

// ===============
// Class Functions
// ===============

void Game::generateTextures()
{
	SDL_Color c = mediaCache.getTextColor();

	p1Tex = mediaCache.getText("P1", font, c);
	p1Tex->setPosition(0, mediaCache.getScrHeight() - p1Tex->getH());

	p2Tex = mediaCache.getText("P2", font, c);
	p2Tex->setPosition(mediaCache.getScrWidth() - p2Tex->getW(), mediaCache.getScrHeight() - p2Tex->getH());

	pauseTex = mediaCache.getText("Pause", smallFont, c);
	pauseTex->setPosition((mediaCache.getScrWidth() / 2 - pauseTex->getW() - p1Tex->getW()) / 2, mediaCache.getScrHeight() - pauseTex->getH());

	menuTex = mediaCache.getText("Menu", smallFont, c);
	menuTex->setPosition((mediaCache.getScrWidth() / 2) + (mediaCache.getScrWidth() / 2 - menuTex->getW() - p1Tex->getW()) / 2, mediaCache.getScrHeight() - menuTex->getH());

	playAgainTex = mediaCache.getText("Play Again", font, c);
	playAgainTex->setPosition(mediaCache.centreX(playAgainTex->getW()), mediaCache.centreY(playAgainTex->getH()) + playAgainTex->getH());

	mainMenuTex = mediaCache.getText("Menu", font, c);
	mainMenuTex->setPosition(mediaCache.centreX(mainMenuTex->getW()), mediaCache.centreY(mainMenuTex->getH()) + 2 * mainMenuTex->getH());

	pausedMsgTex = mediaCache.getText("Paused", font, c);
	pausedMsgTex->setPosition(mediaCache.centreX(pausedMsgTex->getW()), mediaCache.centreY(pausedMsgTex->getH()));
}

void Game::keyPressed(SDL_Event &e, Engine*)
{
	//ignore keyboard input if the game is paused
	if (!paused)
	{
		if (e.type == SDL_KEYDOWN)
		{
			//always handle the player 1 controls, only handle player 2 if they're active
			switch (e.key.keysym.sym)
			{
				case SDLK_w:
					leftBat->setDirectionY(-1);
					break;
				case SDLK_s:
					leftBat->setDirectionY(1);
					break;
			}

			if (humanPlayerCount == 2)
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

			if (humanPlayerCount == 2)
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
}

void Game::mouseClicked(SDL_Event &e, Engine* engine)
{
	int x, y;
	if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
	{
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			//if we have a winner, then process any clicks that are on the end game menu
			if (winningPlayer > 0)
			{
				if (CollisionEngine::checkCollision(playAgainTex->getBox(), x, y))
				{
					p1.reset();
					p2.reset();
					resetBats();
					switch (winningPlayer)
					{
						case 1: resetBall(2);
							break;
						case 2: resetBall(1);
							break;
					}
					winningPlayer = 0;
				}
				else if (CollisionEngine::checkCollision(mainMenuTex->getBox(), x, y))
				{
					engine->changeState(std::make_shared<Title>(mediaCache));
				}
			}
			//otherwise process clicks on pause and menu at the bottom of the screen
			else
			{
				if (CollisionEngine::checkCollision(pauseTex->getBox(), x, y))
				{
					paused = !paused;
				}
				else if (CollisionEngine::checkCollision(menuTex->getBox(), x, y))
				{
					engine->changeState(std::make_shared<Title>(mediaCache));
				}
			}
		}
	}
}

void Game::moveBats(const double dTime)
{
	leftBat->move(mediaCache.getScrHeight(), mediaCache.getScrWidth(), ball->getDirection(), ball->getPosition(), dTime);
	rightBat->move(mediaCache.getScrHeight(), mediaCache.getScrWidth(), ball->getDirection(), ball->getPosition(), dTime);
}

void Game::checkIfBallMoving()
{
	//if the ball isn't moving and on the left of the screen, start it in the direction of the leftBat
	if (!ball->isMoving() && ball->getPosition().x < mediaCache.getScrWidth() / 2 && leftBat->getDirection().y != 0)
	{
		ball->startMoving(1, leftBat->getDirection().y);
	}
	//if the ball isn't moving and on the right of the screen, start it in the direction of the rightBat
	else if (!ball->isMoving() && ball->getPosition().x > mediaCache.getScrWidth() / 2 && rightBat->getDirection().y != 0)
	{
		ball->startMoving(-1, rightBat->getDirection().y);
	}
	//if the ball isn't moving and on the right of the screen, and the rightBat isn't moving and is AI controlled, start the bat moving
	else if (!ball->isMoving() && ball->getPosition().x > mediaCache.getScrWidth() / 2 && rightBat->getID() == 3 && rightBat->getDirection().y == 0)
	{
		rightBat->startMoving();
	}
}

const int Game::moveBall(const double dTime)
{
	return ball->move(mediaCache.getScrHeight(), mediaCache.getScrWidth(), leftBat->getBox(), rightBat->getBox(), dTime);
}

void Game::checkIfGoalScored(const int ballMove)
{
	//leftBat=p1 has scored, so p2 starts with the ball
	if (ballMove == 1)
	{
		resetBats();
		resetBall(2);
		p1.hasScored();
	}
	//rightBat=p2 has scored, so p1 starts with the ball
	else if (ballMove == 2)
	{
		resetBats();
		resetBall(1);
		p2.hasScored();
	}
}

void Game::checkforWinner()
{
	if (p1.getScore() == winningScore)
	{
		winningPlayer = 1;
	}
	else if (p2.getScore() == winningScore)
	{
		winningPlayer = 2;
	}
}

void Game::resetBall(const int startingPlayer)
{
	if (startingPlayer == 1)
	{
		ball->reset(static_cast<int>(leftBat->getPosition().x) + leftBat->getWidth(), mediaCache.getScrHeight());
	}
	else if (startingPlayer == 2)
	{
		ball->reset(static_cast<int>(rightBat->getPosition().x) - rightBat->getWidth(), mediaCache.getScrHeight());
	}
}

void Game::resetBats()
{
	leftBat->reset(mediaCache.getScrHeight());
	rightBat->reset(mediaCache.getScrHeight());
}

void Game::createScoreTex()
{
	std::string scoreStr = std::to_string(p1.getScore()) + " " + std::to_string(p2.getScore());
	scoreTex = mediaCache.getText(scoreStr, font, mediaCache.getTextColor());
	scoreTex->setPosition(mediaCache.centreX(scoreTex->getW()), mediaCache.getScrHeight() - scoreTex->getH());
}

void Game::renderWinningText()
{
	int winnerScore = 0, loserScore = 0;

	switch (winningPlayer)
	{
		case 1:
			winnerScore = p1.getScore();
			loserScore = p2.getScore();
			break;
		case 2:
			winnerScore = p2.getScore();
			loserScore = p1.getScore();
			break;
		default:
			break;
	}
	std::string winningStr = "Player " + std::to_string(winningPlayer) + " wins " + std::to_string(winnerScore) + "-" + std::to_string(loserScore);

	winningTex = mediaCache.getText(winningStr, font, mediaCache.getTextColor());
	winningTex->setPosition(mediaCache.centreX(winningTex->getW()), mediaCache.centreY(winningTex->getH()));
	mediaCache.renderTexture(winningTex, winningTex->getX(), winningTex->getY());

	mediaCache.renderTexture(playAgainTex, playAgainTex->getX(), playAgainTex->getY());
	mediaCache.renderTexture(mainMenuTex, mainMenuTex->getX(), mainMenuTex->getY());
}