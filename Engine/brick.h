#pragma once

#include "rect.h"
#include "Colors.h"
#include "Graphics.h"
#include "ball.h"
#include "beveller.h"

class brick {

public:
	brick() = default;
	brick(const rect& in_rect, Color in_clr);
	void draw(Graphics& gfx);
	bool checkForCollision(const ball& plyBall) const;
	void collide(ball& plyBall);
	vec2 getCenter() const;

private:
	static constexpr float padding = 2.0f;
	Color color;
	rect shape;
	bool bDestroyed = true;

	beveller bevel = beveller(2.0f, 100.0f); //for some reason causes weird reference to brick constructor that is deleted errors when init through the member init list. so we do it here, instead.
};