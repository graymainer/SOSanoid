#pragma once

#include "Graphics.h"
#include "util.h"

class SpriteCodex
{
public:
	// centered drawing of 14x14 sprite
	static void DrawBall( const vec2& center,Graphics& gfx );
	static void drawGameOver(const vec2& topLeft, Graphics& gfx);
	static void drawTitle(const vec2& topLeft, Graphics& gfx);
	static void drawGameWon(const vec2& topLeft, Graphics& gfx);

};