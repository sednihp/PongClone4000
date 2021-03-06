#include "MediaCache.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL_ttf.h"

MediaCache::MediaCache() :	mScrWidth(1024), mScrHeight(768),
							textColor({0,0,0}),
							bgColor({255,255,255}),
							window(nullptr), ren(nullptr), 
							imgCache(ren), fontCache(ren), txtCache(ren)
{
	window = SDL_CreateWindow("Another Pong Clone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mScrWidth, mScrHeight, SDL_WINDOW_SHOWN);
	if(!window)
	{
		std::cout << SDL_GetError() << std::endl;
		exit(2);
	}

	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!ren)
	{
		std::cout << SDL_GetError() << std::endl;
		exit(3);
	}
}

MediaCache::~MediaCache()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);

    SDL_Quit();
}

std::shared_ptr<GameTexture> MediaCache::getImage(const std::string& file)
{
	return imgCache.getImage(file);
}

TTF_Font* MediaCache::getFont(int size)
{
	return fontCache.getFont(size);
}

std::shared_ptr<GameTexture> MediaCache::getText(const std::string& message, TTF_Font* font, const SDL_Color& color)
{
	return txtCache.getText(message, font, color);
}

#include "Util.h"

void MediaCache::renderTexture(std::shared_ptr<GameTexture> tex, const int x, const int y)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
	pos.w = tex->getW();
	pos.h = tex->getH();
 
	SDL_RenderCopy(ren, tex->texture(), NULL, &pos);
}

void MediaCache::drawRectangle(const SDL_Rect& rect, const SDL_Color& c)
{
	SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(ren, &rect);
}

void MediaCache::clearScreen()
{ 
	SDL_SetRenderDrawColor(ren, bgColor.r, bgColor.g, bgColor.b, SDL_ALPHA_OPAQUE); 
	SDL_RenderClear(ren); 
}

const int MediaCache::centreX(const int gtWidth) const
{
	return (mScrWidth - gtWidth) / 2;
}

const int MediaCache::centreY(const int gtHeight) const
{
	return (mScrHeight - gtHeight) / 2;
}

const SDL_Color& MediaCache::getTextColor()
{
	return textColor;
}