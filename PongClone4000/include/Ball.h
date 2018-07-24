#pragma once
#include "Sprite.h"

class Ball : public Sprite {
private:
	SDL_Color color;
	bool moving;
	const int ballWidth = 20;
	const int radius = ballWidth / 2;
	const int movingSpeed = 400;
	double speed;

public:
	Ball(const std::string& img, const int _x, const int scrHeight);
	~Ball();

	const Point2D getPosition();
	const int getRadius() { return radius; }
	const bool isMoving() { return moving; }
	void reverseXDir() { direction.x *= -1; }

	void startMoving(const double xDir, const double yDir);
	bool hasCollided(const SDL_Rect& rect);
	const double distance(const double x1, const double y1, const double x2, const double y2);
	int move(const int scrHeight, const int scrWidth, const SDL_Rect& leftBat, const SDL_Rect& rightBat, const double dTime);
	void reset(const int _x, const int scrHeight);
};