#include <iostream>
#include <SDL3/SDL.h>

#include "maths/vec3.h"
#include "maths/vec4.h"
#include "maths/mat4.h"

#include "renderer/BasicRenderer.h"

int main(int argc, char** argv)
{
	bool status = SDL_Init(SDL_INIT_VIDEO);
	if (!status)
	{
		std::cout << "Failed to initialize SDL3" << std::endl;
	}

	SDL_Window* window = SDL_CreateWindow("3D Renderer", 800, 600, NULL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

	// Init
	Vertex vertices[] = {
		Vertex(-0.5f, -0.5f, -0.5f),
		Vertex( 0.5f, -0.5f, -0.5f),
		Vertex( 0.5f,  0.5f, -0.5f),
		Vertex( 0.5f,  0.5f, -0.5f),
		Vertex(-0.5f,  0.5f, -0.5f),
		Vertex(-0.5f, -0.5f, -0.5f),

		Vertex(-0.5f, -0.5f,  0.5f),
		Vertex( 0.5f, -0.5f,  0.5f),
		Vertex( 0.5f,  0.5f,  0.5f),
		Vertex( 0.5f,  0.5f,  0.5f),
		Vertex(-0.5f,  0.5f,  0.5f),
		Vertex(-0.5f, -0.5f,  0.5f),

		Vertex(-0.5f,  0.5f,  0.5f),
		Vertex(-0.5f,  0.5f, -0.5f),
		Vertex(-0.5f, -0.5f, -0.5f),
		Vertex(-0.5f, -0.5f, -0.5f),
		Vertex(-0.5f, -0.5f,  0.5f),
		Vertex(-0.5f,  0.5f,  0.5f),

		Vertex( 0.5f,  0.5f,  0.5f),
		Vertex( 0.5f,  0.5f, -0.5f),
		Vertex( 0.5f, -0.5f, -0.5f),
		Vertex( 0.5f, -0.5f, -0.5f),
		Vertex( 0.5f, -0.5f,  0.5f),
		Vertex( 0.5f,  0.5f,  0.5f),

		Vertex(-0.5f, -0.5f, -0.5f),
		Vertex( 0.5f, -0.5f, -0.5f),
		Vertex( 0.5f, -0.5f,  0.5f),
		Vertex( 0.5f, -0.5f,  0.5f),
		Vertex(-0.5f, -0.5f,  0.5f),
		Vertex(-0.5f, -0.5f, -0.5f),

		Vertex(-0.5f,  0.5f, -0.5f),
		Vertex( 0.5f,  0.5f, -0.5f),
		Vertex( 0.5f,  0.5f,  0.5f),
		Vertex( 0.5f,  0.5f,  0.5f),
		Vertex(-0.5f,  0.5f,  0.5f),
		Vertex(-0.5f,  0.5f, -0.5f),
	};

	Vertex* transformed = new Vertex[6*6];

	// Camera
	sml::vec3 cameraPosition(0.0f, 0.0f, 0.0f);
	sml::vec3 cameraDirection(0.0f, 0.0f, -1.0f);
	sml::vec3 worldUp(0.0f, 1.0f, 0.0f);

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

		// Clear
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Update
		memcpy(transformed, vertices, sizeof(vertices));
		for (int i = 0; i < 6 * 6; i++)
		{
			// Transform each vertex
			// Local Space to World Space
			sml::vec3 currentVertex(transformed[i].x, transformed[i].y, transformed[i].z);

			sml::mat4 translationMatrix = sml::mat4::CreateTranslationMatrix(0.0f, 0.0f, -2.0f);
			sml::mat4 rotationMatrix = sml::mat4::CreateRotationMatrix(SDL_GetTicks()/20, sml::vec3(1.0f, 0.0f, 0.0f));

			sml::vec4 worldSpaceVector = rotationMatrix * sml::vec4(currentVertex.x, currentVertex.y, currentVertex.z);
			worldSpaceVector = translationMatrix * worldSpaceVector;

			// World Space to View Space

			// View Space to Projected Space (and to NDC)
			sml::mat4 projectionMatrix = sml::mat4::CreatePerspective(-1.0f, 1.0f, 1.0f, -1.0f, -0.1f, -10.0f);
			std::cout << projectionMatrix << std::endl;
			// Perform division by Z
			sml::vec4 projectedVector = projectionMatrix * worldSpaceVector;
			std::cout << projectedVector.w << std::endl;
			projectedVector.x /= projectedVector.w;
			projectedVector.y /= projectedVector.w;
			projectedVector.z /= projectedVector.w;

			transformed[i] = Vertex(projectedVector.x, projectedVector.y, projectedVector.z);
			
			// NDC to Viewport transform
			sml::mat4 NDCToViewport = sml::mat4::CreateNDCToViewportMatrix(800, 600);
			
			sml::vec4 transformedVector = NDCToViewport * sml::vec4(transformed[i].x, transformed[i].y, transformed[i].z);
			transformed[i] = Vertex(transformedVector.x, transformedVector.y, transformedVector.z);
			if (i == 1)
			{
				std::cout << transformed[i].x << ", " << transformed[i].y << std::endl;
			}
		}

		// Draw
		SDL_Color color = { 255, 255, 255, 255 };
		BR_Draw(renderer, RENDER_MODE_TRIANGLES, transformed, 6*6, &color);

		// Show
		SDL_RenderPresent(renderer);
	}

	return 0;
}