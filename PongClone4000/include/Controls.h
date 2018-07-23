#pragma once
#include "State.h"
#include <vector>

class Controls : public State
{
	private:
		std::shared_ptr<GameTexture> title;
		std::vector<std::shared_ptr<GameTexture>> controls;
		std::shared_ptr<GameTexture> menu;
		TTF_Font* font;

		void mouseClicked(SDL_Event &e, Engine* engine);

	public:
		Controls(MediaCache& mc);
		~Controls();

		virtual void enter(Engine* engine);
		virtual void handleEvents(SDL_Event &e, Engine* engine);
		virtual void update(const double dTime, Engine* engine);
		virtual void render();
		virtual void exit(Engine* engine);
};