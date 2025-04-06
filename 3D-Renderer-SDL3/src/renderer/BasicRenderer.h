#pragma once

#include <SDL3/SDL.h>

#define RENDER_MODE_POINT 0
#define RENDER_MODE_TRIANGLES 1

struct Vertex
{
	float x, y, z;

	Vertex();
	Vertex(float x, float y, float z);
};

void BR_Draw(SDL_Renderer* renderer, int renderMode, Vertex* vertices, int vertexCount, SDL_Color* color);