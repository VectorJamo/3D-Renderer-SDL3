#include <iostream>
#include <SDL3/SDL.h>

int main(int argc, char** argv)
{
	bool status = SDL_Init(SDL_INIT_VIDEO);
	if (!status)
	{
		std::cout << "Failed to initialize SDL3" << std::endl;
	}

	SDL_Window* window = SDL_CreateWindow("3D Renderer", 800, 600, NULL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

	bool running = true;
	while (running)
	{
		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_EVENT_QUIT)
			{
				running = false;
			}
		}

		
	}

	return 0;
}