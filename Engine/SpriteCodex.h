#pragma once

#include "Graphics.h"
#include "util.h"

class SpriteCodex
{
public:
	// centered drawing of 14x14 sprite
	static void DrawBall( const vec2& center,Graphics& gfx );
	static void DrawGameOver(const vec2& topLeft, Graphics& gfx);
	static void DrawTitle(const vec2& topLeft, Graphics& gfx);
	static void DrawReady(const vec2& topLeft, Graphics& gfx);
	static void drawGameWon(const vec2& topLeft, Graphics& gfx);

};