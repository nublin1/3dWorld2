#include <SDL.h>
#include <string>

//import std.core;

export module ScreenInfo;

export class ScreenInfo {
public:
	static SDL_Window* mSDL_Window;	
	static SDL_GLContext m_sdlRenderContext;

	std::string m_windowTitle = "";

	//Window focus
	bool mMouseFocus = false;
	bool mKeyboardFocus = false;
	bool mFullScreen = false;
	bool mMinimized = false;
	bool mShown = false;

	ScreenInfo() {
		mSDL_Window = nullptr;
	}

	ScreenInfo(std::string windowTitle) {
		m_windowTitle = windowTitle;
	}

	void handleEvent() {

	}
};


