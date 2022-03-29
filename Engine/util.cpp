#include "util.h"
#include <cmath>

vec2::vec2(float x_in, float y_in)
{
	x = x_in;
	y = y_in;
}

//check if x or y is nan. if either true, we aren't initialized, else we good to go.
//bool vec2::isInit()
//{
//	return isnan(x);
//}

//overloaders
vec2 vec2::operator+(const vec2& rhs) const
{
	return vec2(x + rhs.x, y + rhs.y);
}

vec2 vec2::operator-(const vec2& rhs) const
{
	return vec2(x - rhs.x, y - rhs.y);
}

vec2 vec2::operator-(const float rhs) const
{
	return vec2(x - rhs, y - rhs);
}

bool vec2::operator==(const vec2& rhs) const
{
	return x == rhs.x && y == rhs.y;
}

vec2 vec2::operator*(float rhs) const
{

	return vec2(x * rhs, y * rhs);
}

vec2 & vec2::operator*=(float rhs)
{
	return *this = *this * rhs;
}

vec2 & vec2::operator+=(const vec2 & rhs)
{
	return *this = *this + rhs;
}

float vec2::getLength() const
{
	return std::sqrt(getLengthSq());
}

float vec2::getLengthSq() const
{
	return x * x + y * y;
}

vec2 & vec2::normalize()
{
	return *this = getNormalized();
}

vec2 vec2::getNormalized() const
{
	const float length = getLength();

	if (length == 0.0f)
		return *this;


	return *this * (1.0f / length);
}

//is our vector's x within the range of rangeX to rangeX + size? etc..
bool vec2::isInRange(const float rangeX, const float rangeY, const float size) const
{
	return (x > rangeX && x < rangeX + size) && (y > rangeY && y < rangeY + size);
}
