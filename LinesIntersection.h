#pragma once

#include "mat2f.h"
#include "vec2f.h"
#include <vector>
#include <algorithm>

typedef std::pair<vec2f, vec2f> Line;

bool Intersec(Line line1, Line line2, vec2f* res)
{

	vec2f x = line1.second - line1.first;
	vec2f y = line2.second - line2.first;
	vec2f z = line1.first - line2.first, m = x - y;

	mat2f j((-1.0f) * x, y);

	if (j.det() != 0)
	{
		vec2f t = j.inv() * z;

		if ((t.x < 0 || t.x > 1) || (t.y < 0 || t.y > 1))
		{
			return false;
		}

		*res = line1.first + t.x * x;

		return true;
	}

	return false;
}

std::vector<vec2f> LinesIntersec(std::vector<Line> lines)
{
	std::vector<vec2f> res;

	for (auto line : lines)
	{
		for (auto line_i : lines)
		{
			if (line != line_i)
			{
				vec2f intrsc;

				if (Intersec(line, line_i, &intrsc))
				{
					res.push_back(intrsc);
				}
			}
		}
	}

	std::sort(res.begin(), res.end());

	std::vector<vec2f> intr;

	for (int i = 0; i < res.size(); i += 2)
	{
		intr.push_back(res[i]);
	}

	return intr;

}
