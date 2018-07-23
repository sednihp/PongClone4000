#pragma once
#include "Sprite.h"

class Bat : public Sprite {
private:
	const int speed = 300;
	const int batMargin = 50;
	const int batWidth = 20;
	const int batHeight = 80;
	SDL_Color color;
	SDL_Rect box;
	int batID;
	
public:
	Bat(const int id, const int scrWidth, const int scrHeight);
	~Bat();

	const SDL_Color& getColor() { return color; }
	const SDL_Rect& getBox();
	const int getWidth() { return batWidth;	}
	void move(const int scrHeight, const double deltaTime);
	void setDirection(const Vector2D newDir);
	void setDirectionX(const int newX);
	void setDirectionY(const int newY);
};