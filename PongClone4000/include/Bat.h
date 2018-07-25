#pragma once
#include "Sprite.h"

class Bat : public Sprite {
private:
	const int speed = 400;
	const int batMargin = 50;
	const int batWidth = 20;
	const int batHeight = 80;
	SDL_Color color;
	SDL_Rect box;
	int batID;
	
public:
	Bat(const int id, const int scrWidth, const int scrHeight);
	~Bat();

	const SDL_Color& getColor() const { return color; }
	const SDL_Rect& getBox();
	const int getWidth() const { return batWidth;	}
	const int getID() const { return batID; }
	void move(const int scrHeight, const int scrWidth, const Vector2D& ballDir, const Point2D& ballPos, const double deltaTime);
	void setDirection(const Vector2D& newDir);
	void setDirectionY(const int newY);
	void reset(const int scrHeight);
	void startMoving();
};