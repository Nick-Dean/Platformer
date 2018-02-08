#include "stdafx.h"
#include "DebugDraw.h"
#include "graphics.h"
#include "Globals.h"
#include <SDL2\SDL.h>
#include <SDL2_image\SDL_image.h>

DebugDraw::DebugDraw(Graphics* graphics) : graphics_(graphics)
{
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	SDL_SetRenderDrawColor(graphics_->GetRenderer(), 255, 0, 0, 255);
	SDL_Rect poly;
	poly.x = vertices[0].x * Globals::PIXELS_PER_METER;
	poly.y = vertices[0].y * Globals::PIXELS_PER_METER;
	poly.w = (vertices[0].x * Globals::PIXELS_PER_METER - vertices[1].x * Globals::PIXELS_PER_METER) > 0 ? vertices[0].x * Globals::PIXELS_PER_METER - vertices[1].x * Globals::PIXELS_PER_METER : vertices[1].x * Globals::PIXELS_PER_METER - vertices[0].x * Globals::PIXELS_PER_METER;
	poly.h = (vertices[0].y * Globals::PIXELS_PER_METER - vertices[1].y * Globals::PIXELS_PER_METER) > 0 ? vertices[0].y * Globals::PIXELS_PER_METER - vertices[1].y * Globals::PIXELS_PER_METER : vertices[1].y * Globals::PIXELS_PER_METER - vertices[0].y * Globals::PIXELS_PER_METER;
	SDL_RenderDrawRect(graphics_->GetRenderer(), &poly);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	SDL_SetRenderDrawColor(graphics_->GetRenderer(), 255, 0, 0, 255);
	SDL_Rect poly;
	poly.x = vertices[0].x * Globals::PIXELS_PER_METER;
	poly.y = vertices[0].y * Globals::PIXELS_PER_METER;
	poly.w = (vertices[0].x * Globals::PIXELS_PER_METER - vertices[1].x * Globals::PIXELS_PER_METER) > 0 ? vertices[0].x * Globals::PIXELS_PER_METER - vertices[1].x * Globals::PIXELS_PER_METER : vertices[1].x * Globals::PIXELS_PER_METER - vertices[0].x * Globals::PIXELS_PER_METER;
	poly.h = (vertices[1].y * Globals::PIXELS_PER_METER - vertices[2].y * Globals::PIXELS_PER_METER) > 0 ? vertices[1].y * Globals::PIXELS_PER_METER - vertices[2].y * Globals::PIXELS_PER_METER : vertices[2].y * Globals::PIXELS_PER_METER - vertices[1].y * Globals::PIXELS_PER_METER;
	SDL_RenderDrawRect(graphics_->GetRenderer(), &poly);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	bool a;
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	SDL_SetRenderDrawColor(graphics_->GetRenderer(), 255, 0, 0, 255);
	float d_a = 2 * M_PI / 50,
		angle = d_a;

	b2Vec2 start, end;
	end.x = radius;
	end.y = 0.0f;
	end = end + center;
	for (int i = 0; i != 50; i++)
	{
		start = end;
		end.x = cos(angle) * radius;
		end.y = sin(angle) * radius;
		end = end + center;
		angle += d_a;
		SDL_RenderDrawLine(graphics_->GetRenderer(), start.x, start.y, end.y, end.y);
	}
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	bool a;
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
	bool a;
}

void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	bool a;
}

void DebugDraw::DrawString(int x, int y, const char *string, ...)
{
	bool a;
}

void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& c)
{
	SDL_SetRenderDrawColor(graphics_->GetRenderer(), 255, 0, 0, 255);
	SDL_Rect poly;
	poly.x = aabb->upperBound.x;
	poly.y = aabb->upperBound.y;
	poly.w = aabb->GetExtents().x * 2;
	poly.h = aabb->GetExtents().y * 2;
	SDL_RenderDrawRect(graphics_->GetRenderer(), &poly);
}
