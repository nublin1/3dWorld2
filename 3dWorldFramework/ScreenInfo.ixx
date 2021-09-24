#include <SDL.h>

export module ScreenInfo;

export class ScreenInfo {
public:
	static inline SDL_Window* mSDL_Window = nullptr;
	static SDL_GLContext m_sdlRenderContext;
};