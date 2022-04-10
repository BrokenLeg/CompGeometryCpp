#pragma once

#include <iostream>

class vec2f
{
public:

	vec2f(float a=0, float b=0) : x(a), y(b) {};

	vec2f& operator=(const vec2f& v)
	{
		x = v.x;
		y = v.y;

		return *this;
	}

	float x, y;

	float cross(const vec2f& v) const
	{
		return x * v.y - y * v.x;
	}

	friend bool operator==(const vec2f& v, const vec2f& u);

	bool operator!=(const vec2f& v)
	{
		return !(*this == v);
	}

	vec2f operator-(const vec2f& v) const
	{
		return vec2f(x - v.x, y - v.y);
	}

	vec2f operator+(const vec2f& v) const
	{
		return vec2f(x + v.x, y + v.y);
	}


	vec2f operator*(float k)
	{
		return { x * k, y * k };
	}

	friend vec2f operator*(float k, const vec2f& v);

	friend bool operator<(const vec2f& v, const vec2f& u);

	friend std::ostream& operator<<(std::ostream& os, const vec2f& v);

	float magnitude()
	{
		return sqrt(x * x + y * y);
	}

	

};

bool operator<(const vec2f& v, const vec2f& u) {

	if (v.x == u.x)
	{
		return (v.y < u.y);
	}

	return v.x < u.x;
}
bool operator==(const vec2f& v, const vec2f& u)
{
	return (v.x == u.x) && (v.y == u.y);
}

vec2f operator*(float k, const vec2f& v)
{
	return { v.x * k, v.y * k };
}

std::ostream& operator<<(std::ostream& os, const vec2f& v)
{
	std::cout << "(" << v.x << ", " << v.y << ")";

	return os;
}

bool left(const vec2f& a, const vec2f& b) // b is left to a
{
	return (a.cross(b) > 0);
}

bool isRightTurn(const vec2f& a, const vec2f& b, const vec2f& c)
{
	return !left(b - a, c - a);
}