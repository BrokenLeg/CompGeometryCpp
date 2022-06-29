#pragma once

#include "mat2f.h"
#include "vec2f.h"

#include <vector>
#include <iostream>

typedef std::vector<vec2f> trngl;


void reverse(std::vector<vec2f>& points)
{
	std::vector <vec2f> r;

	int N = points.size();

	for (int i = N - 1; i >= 0; i--)
	{
		r.push_back(points[i]);
	}

	points = r;
}

bool isClock(const std::vector<vec2f>& points)
{
	if (points.size() == 0)
	{
		return true;
	}

	vec2f p = points[0];
	int j = 0, N = points.size();

	for (int i = 1; i < N; i++)
	{
		if (points[i].y < p.y)
		{
			p.y = points[i].y;
			j = i;
		}
		if (points[i].y == p.y)
		{
			if (points[i].x > p.x)
			{
				p.y = points[i].y;
				j = i;
			}
		}

	}

	auto a = points[j], c = points[(j + 1) % N], b = points[(j == 0) ? N - 1 : j - 1];

	return (b - a).cross(c - a) > 0;
}

std::vector<trngl> Triangulation(const std::vector<vec2f>& Polynom)
{

	int N = Polynom.size();

	int vertexIn = N;
	int i = 0;

	std::vector<bool> out(N, false);

	std::vector<trngl> res;

	while (vertexIn > 3)
	{

		if (!out[i])
		{

			int prevInd = (i-1)%N, nxtInd;

			vec2f prev;

			for (int k = i; k != (i + 2) % N;)
			{

				if (k != i && !out[k])
				{
					prev = Polynom[k];
					prevInd = k;
					break;
				}


				if (k == 0)
				{
					k = N - 1;
				}
				else
				{
					k--;
				}

			}

			vec2f cur = Polynom[i];
			vec2f next;

			int maxNxt;

			if (i == 0 || i == 1)
			{
				maxNxt = N - 1 - i;
			}
			else
			{
				maxNxt = i - 2;
			}

			for (int k = i; k != maxNxt;)
			{

				if (k != i && !out[k])
				{
					next = Polynom[k];
					nxtInd = k;
					break;
				}


				if (k == N-1)
				{
					k = 0;
				}
				else
				{
					k++;
				}

			}

			trngl T = { prev, cur, next };

			std::cout << T[0] << T[1] << T[2] << "\n\n";

			if (isRightTurn(prev, cur, next))
			{

				bool isEmpty = true;

				for (int j = 0; j < N; j++)
				{
					

					if ( j != i && j != nxtInd && j != prevInd && !out[j])
					{
						if (insideTriangle(T, Polynom[j]))
						{
							isEmpty = false;
							break;
						}
					}
				}

				if (isEmpty)
				{
					res.push_back(T);
					out[i] = true;
					vertexIn--;
				}

			}
		}

		i = (i + 1) % N;

	}

	trngl t;

	for (int i = 0; i < N; i++)
	{
		if (!out[i])
		{
			t.push_back(Polynom[i]);
		}
	}

	res.push_back(t);

	return res;
}