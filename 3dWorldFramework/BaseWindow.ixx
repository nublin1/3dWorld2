
#include <GL\glew.h>
#ifdef	_WIN32
#include <GL\wglew.h>
#else
#include <GL/glxew.h>
#endif

#include <string>
#include <sstream>
#include <iostream>

#include <SDL.h>



export module BaseWindow;

export class BaseWindow {
public:
	BaseWindow() {};	
	virtual ~BaseWindow() {};

	void Init(SDL_Window* mWindow, SDL_Renderer* mRenderer, SDL_GLContext sdlRenderContext, int mWindowID) {
		this->mWindow = mWindow;
		this->mRenderer = mRenderer;
		this->m_sdlRenderContext = sdlRenderContext;
		this->mWindowID = mWindowID;
		//this->m_windowTitle = windowTitle;
	}

	void handleEvent() {
		SDL_Event event;

		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_WINDOWEVENT && event.window.windowID == mWindowID) {
				//Caption update flag
				bool updateCaption = false;

				SDL_GL_GetDrawableSize(mWindow, &mWidth, &mHeight);
				glViewport(0, 0, mWidth, mHeight);


				switch (event.window.event)
				{
					//Window appeared
				case SDL_WINDOWEVENT_SHOWN:
					mShown = true;
					break;

					//Window disappeared
				case SDL_WINDOWEVENT_HIDDEN:
					mShown = false;
					break;

					//Get new dimensions and repaint
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					mWidth = event.window.data1;
					mHeight = event.window.data2;
					SDL_RenderPresent(mRenderer);
					break;

					//Repaint on expose
				case SDL_WINDOWEVENT_EXPOSED:
					SDL_RenderPresent(mRenderer);
					break;

					//Mouse enter
				case SDL_WINDOWEVENT_ENTER:
					mMouseFocus = true;
					updateCaption = true;
					break;

					//Mouse exit
				case SDL_WINDOWEVENT_LEAVE:
					mMouseFocus = false;
					updateCaption = true;
					break;

					//Keyboard focus gained
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					mKeyboardFocus = true;
					updateCaption = true;
					break;

					//Keyboard focus lost
				case SDL_WINDOWEVENT_FOCUS_LOST:
					mKeyboardFocus = false;
					updateCaption = true;
					break;

					//Window minimized
				case SDL_WINDOWEVENT_MINIMIZED:
					mMinimized = true;
					break;

					//Window maxized
				case SDL_WINDOWEVENT_MAXIMIZED:
					mMinimized = false;
					break;

					//Window restored
				case SDL_WINDOWEVENT_RESTORED:
					mMinimized = false;
					break;

					//Hide on close
				case SDL_WINDOWEVENT_CLOSE:
					SDL_HideWindow(mWindow);
					break;
				}

				//Update window caption with new data
				if (updateCaption)
				{
					std::stringstream caption;
					caption << m_windowTitle << " - ID: " << mWindowID << " MouseFocus:" << ((mMouseFocus) ? "On" : "Off") << " KeyboardFocus:"
						<< ((mKeyboardFocus) ? "On" : "Off");
					SDL_SetWindowTitle(mWindow, caption.str().c_str());
				}
			}
		}
	}

	void focus() {
		//Restore window if needed
		if (!mShown) {
			SDL_ShowWindow(mWindow);
		}

		//Move window forward
		SDL_RaiseWindow(mWindow);
	}	

protected:
	//Window data
	static inline SDL_Window* mWindow = nullptr;
	static inline SDL_Renderer* mRenderer = nullptr;
	static inline SDL_GLContext m_sdlRenderContext = nullptr;
	static inline int mWindowID = 0;
	static inline std::string m_windowTitle = "";

	//Window focus
	bool mMouseFocus = false;
	bool mKeyboardFocus = false;
	bool mFullScreen = false;
	bool mMinimized = false;
	bool mShown = false;

public:
	//Window dimensions
	int mWidth = 0;
	int mHeight = 0;
};