#include "BasicRenderer.h"

#include <cassert>

Vertex::Vertex()
	:x(0), y(0), z(0)
{
}

Vertex::Vertex(float x, float y, float z)
	:x(x), y(y), z(z)
{
}

void BR_Draw(SDL_Renderer* renderer, int renderMode, Vertex* vertices, int vertexCount, SDL_Color* color)
{
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	switch (renderMode)
	{
	case RENDER_MODE_POINT:
		for (int i = 0; i < vertexCount; i++)
		{
			SDL_RenderPoint(renderer, vertices[i].x, vertices[i].y);
		}
		break;
	case RENDER_MODE_TRIANGLES:
		// Raise an assert if vertexCount is not a multiple of 3
		assert(vertexCount % 3 == 0);
		for (int i = 0; i < vertexCount; i += 3)
		{
			Vertex vert1 = vertices[i];
			Vertex vert2 = vertices[i + 1];
			Vertex vert3 = vertices[i + 2];

			// Draw line vert1-vert2 then vert2-vert3 and finally vert3-vert1
			SDL_RenderLine(renderer, vert1.x, vert1.y, vert2.x, vert2.y);
			SDL_RenderLine(renderer, vert2.x, vert2.y, vert3.x, vert3.y);
			SDL_RenderLine(renderer, vert3.x, vert3.y, vert1.x, vert1.y);
		}
		break;
	}
}
