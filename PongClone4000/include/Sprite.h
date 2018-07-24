#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED
#include "Util.h"
#include <string>
#include "SDL.h"

class Sprite
{
protected:
	Point2D position;
	Vector2D direction;
	std::string image;

public:
	Sprite();
	Sprite(const std::string& img);
	~Sprite();

	const Point2D& getPosition() const { return position; }
	const Vector2D& getDirection() const { return direction; }
	const std::string& getImage() const { return image; }
};

#endif // SPRITE_H_INCLUDED