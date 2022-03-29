#pragma once

#include "util.h"
#include "Colors.h"

class rect {

public:

	rect() = default;
	rect(const float in_left, const float in_right, const float in_top, const float in_bottom);
	rect(const vec2& topLeft, const vec2& bottomRight);
	rect(const vec2& topLeft, const float width, const float height);
	bool isOverlapping(const rect& overlapped) const;
	static rect fromCenter(const vec2& center, const float halfWidth, const float halfHeight);

	rect offset(float offset) const;

	vec2 getOrigin() const;

	


	float left;
	float right;
	float top;
	float bottom;
	
};