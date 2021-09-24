
#include <GL\glew.h>
#ifdef	_WIN32
#include <GL\wglew.h>
#else
#include <GL/glxew.h>
#endif

#include <cstdio>

#include <SDL.h>

import std.core;

import ScreenInfo;
import Time;

export module BaseApplication;

export class BaseApplication {
public:
	BaseApplication() {};
	~BaseApplication() {};

	int initializeApp() {

		GetSystemInfo(&sysinfo);

		int initOK = 0;
		initOK = initializeSDL();
		initOK = initializeGLEW();

		return initOK;
	}

	void mainLoop()
	{
		while (m_mainLoopDone == false) {
			SDL_Event event;

			Time::computeDeltaTime();		
			

			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT)
					m_mainLoopDone = true;
				if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(mSDL_Window))
					m_mainLoopDone = true;
			}
		}
	}

	void exitApplication() {
		SDL_Quit();
	}

	bool getIsMainLoopDone() { return m_mainLoopDone; }

private:
	SYSTEM_INFO sysinfo;
	SDL_Window* mSDL_Window = nullptr;
	SDL_Surface* window_surface = nullptr;
	SDL_GLContext m_sdlRenderContext;
	SDL_Renderer* mRenderer = nullptr;
	SDL_DisplayMode current;
	int mWindowID = 0;

	bool m_mainLoopDone = false;

	//Window focus
	bool mMouseFocus = false;
	bool mKeyboardFocus = false;
	bool mFullScreen = false;
	bool mMinimized = false;
	bool mShown = false;

	int initializeSDL() {
		SDL_SetMainReady();
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			printf("Error: %s\n", SDL_GetError());
			return -1;
		}
		//Create window
		mSDL_Window = SDL_CreateWindow("3d World", 50, 100, 1280, 1024, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (mSDL_Window == NULL)
		{
			printf("Game Window could not be created!\n");
			printf("Error: %s\n", SDL_GetError());
			return 0;
		}
		else {
			//Grab window identifier
			mWindowID = SDL_GetWindowID(mSDL_Window);
			ScreenInfo::mSDL_Window = mSDL_Window;
			//Flag as opened
			mShown = true;
			mMouseFocus = true;
			mKeyboardFocus = true;

		}

		// This line causes a segmentation fault
		window_surface = SDL_GetWindowSurface(mSDL_Window);
		m_sdlRenderContext = SDL_GL_CreateContext(mSDL_Window);
		if (m_sdlRenderContext == NULL) {
			printf("context is not associated with the window.!\n");
			printf("Error: %s\n", SDL_GetError());
		}

		mRenderer = SDL_CreateRenderer(mSDL_Window, -1, 0);

		if (mRenderer == NULL) {
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			SDL_DestroyWindow(mSDL_Window);
			mSDL_Window = NULL;
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GetCurrentDisplayMode(0, &current);

		return 1;
	}

	int initializeGLEW() {
		//glewExperimental = GL_TRUE;     // To expose all extensions with valid entry points.  2015-07-02
		GLenum err = glewInit();
		if (GLEW_OK != err) {
			fprintf(stderr, "Error: %p\n", glewGetErrorString(err));
			return 0;
		}

		return 1;
	}


};