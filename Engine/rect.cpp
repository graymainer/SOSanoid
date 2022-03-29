#include "rect.h"

rect::rect(const float in_left, const float in_right, const float in_top, const float in_bottom)
	:
	left(in_left),
	right(in_right),
	top(in_top),
	bottom(in_bottom)
{
}

rect::rect(const vec2 & topLeft, const vec2 & bottomRight)
	:
	rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

rect::rect(const vec2 & topLeft, const float width, const float height)
	:
	rect(topLeft, topLeft + vec2(width, height))
{
}

rect rect::fromCenter(const vec2 & center, const float halfWidth, const float halfHeight)
{
	const vec2 half(halfWidth, halfHeight);
	return rect(center - half, center + half);
}

rect rect::offset(float offset) const
{
	return rect(left - offset, right + offset, top - offset, bottom + offset);
}

vec2 rect::getOrigin() const
{
	return vec2((left + right) / 2.0f, (top + bottom) / 2.0f);
}


bool rect::isOverlapping(const rect & overlapped) const
{
	return (right > overlapped.left && left < overlapped.right) && (bottom > overlapped.top && top < overlapped.bottom);
}
