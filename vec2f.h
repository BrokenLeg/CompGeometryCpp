#pragma once

#include <iostream>
#include <vector>

enum CompareType { X, Y };
CompareType Type = X;

class vec2f
{
public:

	vec2f(float a=0, float b=0) : x(a), y(b) {};

	static void setType(CompareType type)
	{
		Type = type;
	}

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

	float operator*(const vec2f& v) const
	{
		return x*v.x + y*v.y ;
	}

	friend bool operator==(const vec2f& v, const vec2f& u);

	bool operator!=(const vec2f& v)
	{
		return !(*this == v);
	}

	vec2f operator-(const vec2f& v) const
	{
		float _x = x - v.x;
		float _y = y - v.y;

		return vec2f(_x, _y);
	}

	vec2f operator+(const vec2f& v) const
	{
		float _x = x + v.x;
		float _y = y + v.y;

		float e = 0.0001;

		if (abs(_x) < e)
		{
			_x = 0;
		}

		if (abs(_y) < e)
		{
			_y = 0;
		}


		return vec2f(_x, _y);
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

	if (Type == X)
	{
		if (v.x == u.x)
		{
			return (v.y < u.y);
		}

		return v.x < u.x;
	}
	else
	{
		if (v.y == u.y)
		{
			return v.x < u.y;
		}

		return v.y < u.y;
	}
}
bool operator==(const vec2f& v, const vec2f& u)
{
	return (v.x == u.x) && (v.y == u.y);
}

vec2f operator*(float k, const vec2f& v)
{
	float _x = k*v.x;
	float _y = k*v.y;

	float e = 0.001;

	if (abs(_x) < e)
	{
		_x = 0;
	}

	if (abs(_y) < e)
	{
		_y = 0;
	}


	return vec2f(_x, _y);

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

bool insideTriangle(const std::vector<vec2f>& Triangle, vec2f p)
{

	vec2f x = Triangle[0] - Triangle[1], z = Triangle[2] - Triangle[0], y = Triangle[2] - Triangle[1];

	float S = abs(x.cross(z));

	float S1 = abs(x.cross(p - Triangle[0]));
	float S2 = abs(z.cross(p - Triangle[0]));
	float S3 = abs(y.cross(p - Triangle[1]));

	float e = 0.0001;

	return (abs(S1 + S2 + S3 - S) < e);
}