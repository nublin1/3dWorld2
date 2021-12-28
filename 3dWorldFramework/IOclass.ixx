#include <SDL.h>

export module IOclass;

export class IOClass {
protected:
	static SDL_Event event;

public:
	IOClass() {};
	~IOClass() {};

	SDL_Event getEvent() {
		return event;
	}
};