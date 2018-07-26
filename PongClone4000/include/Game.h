#pragma once
#include "State.h"
#include "Bat.h"
#include "Ball.h"
#include "Player.h"
#include <memory>
#include <vector>

class Game : public State {
private:
	TTF_Font * font;
	TTF_Font* smallFont;
	std::shared_ptr<GameTexture> p1Tex;
	std::shared_ptr<GameTexture> p2Tex;
	std::shared_ptr<GameTexture> scoreTex;
	std::shared_ptr<GameTexture> pauseTex;
	std::shared_ptr<GameTexture> menuTex;
	std::shared_ptr<GameTexture> winningTex;
	std::shared_ptr<GameTexture> playAgainTex;
	std::shared_ptr<GameTexture> mainMenuTex;
	std::shared_ptr<GameTexture> pausedMsgTex;
	std::unique_ptr<Bat> leftBat;
	std::unique_ptr<Bat> rightBat;
	std::unique_ptr<Ball> ball;
	int humanPlayerCount, winningPlayer;
	const int winningScore = 3;
	bool paused;
	SDL_Rect net;
	Player p1, p2;

	void generateTextures();
	void keyPressed(SDL_Event &e, Engine* engine);
	void mouseClicked(SDL_Event &e, Engine* engine);
	void moveBats(const double dTime);
	void checkIfBallMoving();
	const int moveBall(const double dTime);
	void checkIfGoalScored(const int ballMove);
	void checkforWinner();
	void resetBats();
	void resetBall(const int startingPlayer);
	void createScoreTex();
	void renderWinningText();

public:
	Game(MediaCache& mc, const int numPlayers);
	~Game();

	virtual void enter(Engine* engine);
	virtual void handleEvents(SDL_Event &e, Engine* engine);
	virtual void update(const double dTime, Engine* engine);
	virtual void render();
	virtual void exit(Engine* engine);
};