#pragma once

#include <iostream>

class vec2f
{
public:

	vec2f(float a, float b) : x(a), y(b) {};

	float x, y;

	float cross(const vec2f& v) const
	{
		return x * v.y - y * v.x;
	}

	bool operator==(const vec2f& v)
	{
		return (x == v.x && y == v.y);
	}

	bool operator!=(const vec2f& v)
	{
		return !(*this == v);
	}

	vec2f operator-(const vec2f& v)
	{
		return vec2f(x - v.x, y - v.y);
	}

	friend std::ostream& operator<<(std::ostream& os, const vec2f& v);

	float magnitude()
	{
		return sqrt(x * x + y * y);
	}

	bool operator<(const vec2f& v)
	{
		if (x == v.x)
		{
			return (y > v.y);
		}

		return x > v.x;
	}
};

std::ostream& operator<<(std::ostream& os, const vec2f& v)
{
	std::cout << "( " << v.x << ", " << v.y << ")";

	return os;
}

bool left(const vec2f& a, const vec2f& b) // b is left to a
{
	return (a.cross(b) > 0);
}