#pragma once

#include "vec2f.h"

typedef std::vector<vec2f> polygon;

bool insidePolygon(const std::vector<vec2f>& polygon, const vec2f& p)
{

	int N = polygon.size();

	int count = 0;

	for (int i = 0; i < N; i++)
	{
		vec2f a = polygon[i], b = polygon[(i + 1) % N];

		if ((p.y < a.y) != (p.y < b.y))
		{

			float k = (b.x - a.x) / (b.y - a.y);

			if (p.x < ((p.y - a.y) * k + a.x))
			{
				count++;
			}
		}
	}

	return count % 2;
}

vec2f n(const std::pair<vec2f, vec2f>& Line)
{
	auto e = Line.second - Line.first;
	e = (1.0f / e.magnitude()) * e;

	return {(-1)*e.y, e.x};
}

float proj(const vec2f& p, const vec2f& e)
{
	//e is normalized
	return (p*e);
}

bool segmentsIntersection(float a1, float b1, float a2, float b2)
{
	if (a1 == a2)
	{
		return true;
	}

	if (a1 < a2)
	{
		return b1 >= a2;
	}

	if (a2 < a1)
	{
		return b2 >= a1;
	}
}

bool SAT(const std::vector<vec2f>& p1, const std::vector<vec2f>& p2)
{

	int N = p1.size(), M = p2.size();

	for (int i = 0; i < N; i++)
	{
		auto cur = p1[i], nxt = p1[(i + 1) % N];

		auto e = n({cur, nxt});

		float min1 = INFINITY, max1 = -INFINITY;

		for (int j = 0; j < N; j++)
		{
			float t = proj(p1[j], e);

			if (t < min1)
			{
				min1 = t;
			}

			if (t > max1)
			{
				max1 = t;
			}

		}

		float min2 = INFINITY, max2 = -INFINITY;

		for (int j = 0; j < M; j++)
		{
			float t = proj(p2[j], e);

			if (t < min2)
			{
				min2 = t;
			}

			if (t > max2)
			{
				max2 = t;
			}

		}

		if (!segmentsIntersection(min1, max1, min2, max2))
			return false;

	}
	for (int i = 0; i < M; i++)
	{
		auto cur = p2[i], nxt = p2[(i + 1) % M];

		auto e = n({ cur, nxt });

		float min1 = INFINITY, max1 = -INFINITY;

		for (int j = 0; j < N; j++)
		{
			float t = proj(p1[j], e);

			if (t < min1)
			{
				min1 = t;
			}

			if (t > max1)
			{
				max1 = t;
			}

		}

		float min2 = INFINITY, max2 = -INFINITY;

		for (int j = 0; j < M; j++)
		{
			float t = proj(p2[j], e);

			if (t < min2)
			{
				min2 = t;
			}

			if (t > max2)
			{
				max2 = t;
			}

		}

		if (!segmentsIntersection(min1, max1, min2, max2))
			return false;

	}

	return true;
}