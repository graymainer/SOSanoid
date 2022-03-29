#pragma once

/*
	2D VECTOR CLASS
	-FEATURES-
	+, -, ==, *, *= += operators supported
	length of vectors can be gotten
	normalized vectors are supported. a mutator and a simple getter exist for this.
	axes are using floating-point numbers.
	!currently no way to check for initialization!
	*/
class vec2 {
public:
	vec2() = default;
	vec2(float x_in, float y_in);

	//check if x or y is nan. if either true, we aren't initialized, else we good to go.
	//bool isInit(); 


	//operator overloads

	vec2 operator+(const vec2& rhs) const;

	vec2 operator-(const vec2& rhs) const;
	vec2 operator-(const float rhs) const;

	bool operator==(const vec2& rhs) const;

	vec2 operator*(float rhs) const;

	vec2& operator*=(float rhs);

	vec2& operator+=(const vec2& rhs);

	float getLength() const; //expensive! finds square root
	float getLengthSq() const;

	vec2& normalize();
	vec2 getNormalized() const;

	//is our vector's x within the range of rangeX to rangeX + size? etc..
	//float, float, float
	bool isInRange(const float rangeX, const float rangeY, const float size) const;

public:
	float x, y;
};