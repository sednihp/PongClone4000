#ifndef MEDIACACHE_H
#define MEDIACACHE_H

#include "SDL.h"
#include <string>
#include "ImageCache.h"
#include "FontCache.h"
#include "TextCache.h"

class MediaCache
{
	private:
		const int mScrWidth, mScrHeight;
		SDL_Window* window;
		SDL_Renderer* ren;
		SDL_Color textColor, bgColor;

		ImageCache imgCache;
		FontCache fontCache;
		TextCache txtCache;

		MediaCache &operator=(const MediaCache&);
		MediaCache(const MediaCache&);

	public:
		MediaCache();
		~MediaCache();

		std::shared_ptr<GameTexture> getImage(const std::string& file);
		TTF_Font* getFont(const int size);
		std::shared_ptr<GameTexture> getText(const std::string& message, TTF_Font* font, const SDL_Color& color);

		void renderTexture(std::shared_ptr<GameTexture> tex, const int x, const int y);
		void drawRectangle(const SDL_Rect& rect, const SDL_Color& color);

		void clearScreen();
		void updateScreen() { SDL_RenderPresent(ren); }

		const int getScrWidth() const { return mScrWidth; }
		const int getScrHeight() const { return mScrHeight; }
		const int centreX(const int gtWidth) const;
		const int centreY(const int gtHeight) const;
		const SDL_Color& getTextColor();	
};

#endif