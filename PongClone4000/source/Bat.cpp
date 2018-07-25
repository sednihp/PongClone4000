#include "Bat.h"

Bat::Bat(const int id, 
		const int scrWidth, 
		const int scrHeight) : color({ 0,0,0 }),
								batID(id)
{
	//case 1 is always the left bat
	//case 2 is multiplayer right bat
	//case 3 is single player right bat
	switch (batID) {
		case 1: 
			box.x = batMargin;
			break;
		case 2:
		case 3: 
			box.x = scrWidth - batMargin - batWidth;
			break;
	}

	box.y = (scrHeight - batHeight) / 2;
	box.w = batWidth;
	box.h = batHeight;

	position.x = box.x;
	position.y = box.y;
}

Bat::~Bat()
{

}

void Bat::move(const int scrHeight, const int scrWidth, const Vector2D& ballDir, const Point2D& ballPos, const double deltaTime)
{
	if (batID == 3)
	{
		const int centreBatY = (scrHeight - batHeight) / 2;

		//if the ball is moving left, move the bat back to the middle
		if (ballDir.x < 0)
		{
			if (position.y > centreBatY && direction.y > 0)
				direction.y = 0;
			else if (position.y < centreBatY && direction.y < 0)
				direction.y = 0;
			else if (centreBatY - position.y > batHeight / 2 && direction.y == 0)
				direction.y = 1;
			else if (position.y - centreBatY > batHeight / 2 && direction.y == 0)
				direction.y = -1;
		}
		//if the ball is moving right, try to align the centre of the bat with the centre of the ball
		else if (ballDir.x > 0 && ballPos.x > scrWidth / 2)
		{
			const double centreOfBat = position.y + batHeight / 2;

			if (ballPos.y < centreOfBat && direction.y > 0)
				direction.y = 0;
			else if (ballPos.y > centreOfBat && direction.y < 0)
				direction.y = 0;
			else if (ballPos.y < centreOfBat && direction.y == 0)
				direction.y = -1;
			else if (ballPos.y > centreOfBat && direction.y == 0)
				direction.y = 1;
		}
	}

	position.y += direction.y * speed * deltaTime;

	if (position.y < 0)
	{
		position.y = 0;
	}
	else if (position.y + batHeight > scrHeight)
	{
		position.y = scrHeight - batHeight;
	}
}

void Bat::setDirection(const Vector2D& newDir)
{
	direction = newDir;
}

void Bat::setDirectionY(const int _y)
{
	direction.y = _y;
}

const SDL_Rect& Bat::getBox()
{
	box.x = static_cast<int>(position.x);
	box.y = static_cast<int>(position.y);

	return box;
}

void Bat::reset(const int scrHeight)
{
	direction.y = 0;
	box.y = (scrHeight - batHeight) / 2;
	position.y = box.y;
}

void Bat::startMoving()
{
	switch (rand() % 2)
	{
		case 0:
			direction.y = -1;
			break;
		case 1: 
			direction.y = 1;
			break;
	}
}