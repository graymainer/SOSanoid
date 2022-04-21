#pragma once

#include "util.h"
#include "Graphics.h"
#include "Colors.h"
#include "ball.h"
#include "Mouse.h"
#include "Sound.h"

class paddle {
public:
	paddle(const vec2& in_pos, const float in_halfWidth, const float in_halfHeight, const float in_wingWidth, const Color& in_clr0, const Color& in_clr1);

	void update(const Mouse& mou, const float dt);
	void draw(Graphics& gfx);

	bool paddleBall(ball& plyBall);

	void clampToScreen(const rect& bounds);

	rect getRect();

	void resetCooldown();
	void startCooldown();

	//power up stuff

	void boostSpeed();

private:
	

	vec2 pos;
	float speed = 8 * 60.0f;
	float halfWidth;
	float halfHeight;
	const float wingWidth;
	Color paddleClr;
	Color paddleWingClr;
	bool bCooldown = false;

	static constexpr float varianceFactor = 40;

	//power up stuff
	float timeElapsed = 0.0f;

	float speedBoostTimer = 10.0f;

	bool bSpedUp = false;

	Sound paddleSnd;


};