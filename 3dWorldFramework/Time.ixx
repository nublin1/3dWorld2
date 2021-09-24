#include <GL\glew.h>

#include <SDL.h>

export module Time;

export class Time {
private:
	static inline Uint64 m_lastFrameTime = 0;
	static inline Uint64 m_actualTime = SDL_GetPerformanceCounter();
	static inline GLdouble deltaTime = 0.0;

public:
	static void computeDeltaTime() {
		m_lastFrameTime = m_actualTime;
		m_actualTime = SDL_GetPerformanceCounter();
		deltaTime = static_cast<double>((m_actualTime - m_lastFrameTime) * 1000 / SDL_GetPerformanceFrequency());
	}

	static GLdouble GetDeltaTime() {
		return deltaTime;
	}
};