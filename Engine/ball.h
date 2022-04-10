#pragma once


#include "util.h"
#include "Graphics.h"
#include "SpriteCodex.h"

class ball {

public:
	ball(vec2 in_pos, vec2 in_vel);

	void reboundX();
	void reboundY(float variance);
	void draw(Graphics& gfx);
	void update(float dt);
	vec2 getVelocity() const;
	bool checkForBoundsCollision(const rect& wall);
	vec2 getPos();
	bool checkForFailure(const rect& wall);

	rect getBoundingBox() const;

private:

	static constexpr float radius = 7.0f;

	//rect bb; //our bounding box that represents us physically

	vec2 pos;
	vec2 vel;
	static constexpr float maxVel = 650.0f;
	static constexpr float baseX = 300.0f;

};