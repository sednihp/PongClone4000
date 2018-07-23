#include "Sprite.h"

Sprite::Sprite(const std::string& img) : image(img), 
										position(0, 0),
										direction(0, 0)
{

}

Sprite::Sprite() : Sprite("")
{

}


Sprite::~Sprite()
{

}
