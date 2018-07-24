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
	std::vector<std::shared_ptr<GameTexture>> playerNames;
	std::shared_ptr<GameTexture> score;
	std::unique_ptr<Bat> leftBat;
	std::unique_ptr<Bat> rightBat;
	std::unique_ptr<Ball> ball;
	const int playerCount;
	SDL_Rect net;
	Player p1, p2;

	void keyPressed(SDL_Event &e, Engine* engine);

public:
	Game(MediaCache& mc, const int numPlayers);
	~Game();

	virtual void enter(Engine* engine);
	virtual void handleEvents(SDL_Event &e, Engine* engine);
	virtual void update(const double dTime, Engine* engine);
	virtual void render();
	virtual void exit(Engine* engine);
};