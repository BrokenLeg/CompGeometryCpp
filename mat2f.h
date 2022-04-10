#pragma once

#include "vec2f.h"
#include <iostream>

class mat2f
{
public:

	mat2f(float a, float b, float c, float d)
	{
		arr[0] = a;
		arr[1] = b;
		arr[2] = c;
		arr[3] = d;
	}

	mat2f(const vec2f& v, const vec2f& u)
	{
		arr[0] = v.x;
		arr[1] = u.x;
		arr[2] = v.y;
		arr[3] = u.y;
	}

	float arr[4];

	float get(int i, int j) const
	{
		return arr[i * 2 + j];
	}

	vec2f operator*(const vec2f& v)
	{
		return { v.x * arr[0] + v.y * arr[1], v.x * arr[2] + v.y * arr[3] };
	}

	mat2f operator*(float k)
	{
		return { arr[0] * k, arr[1] * k, arr[2] * k, arr[3] * k };
	}

	friend std::ostream& operator<<(std::ostream& os, const mat2f& m);

	float det()
	{
		return arr[0] * arr[3] - arr[1] * arr[2];
	}

	mat2f inv()
	{
		if (det() == 0)
		{
			return *this;
		}

		return mat2f(arr[3], -arr[1], -arr[2], arr[0]) * (1.0f / det());
	}
};

std::ostream& operator<<(std::ostream& os, const mat2f& m)
{
	std::cout << "[" << m.get(0, 0) << " " << m.get(0, 1) << "\n "
		<< m.get(1, 0) << " " << m.get(1, 1) << "]\n";

	return os;
}
