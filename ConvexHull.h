#pragma once

#include "vec2f.h"
#include <vector>
#include <algorithm>

std::vector<vec2f> clockwise(std::vector<std::pair<vec2f, vec2f>> edges, int n)
{

	if (edges.empty())
	{
		return {};
	}

	std::vector<vec2f> res;

	vec2f p = edges[0].first, q = edges[0].second;

	while (res.size() < n)
	{

		res.push_back(p);

		p = q;

		//find {p = q, r} pair

		for (auto pair : edges)
		{
			if (pair.first == p)
			{
				q = pair.second;
				break;
			}
		}

	}

	return res;
}

std::vector<vec2f> slowConvexHull(std::vector<vec2f> points)
{
	std::vector<std::pair<vec2f, vec2f>> res;

	for (auto p : points)
	{
		for (auto q : points)
		{
			if (p != q)
			{

				vec2f l = q - p; //from p to q

				bool valid = true;

				//std::cout << p << ", " << q << "\n";

				for (auto r : points)
				{
					if (r != p && r != q)
					{

						//std::cout << r;

						if (left(l, r - q))
						{

							//std::cout << " -\n";

							valid = false;
						}
						else
						{
							//std::cout << " +\n"; //right
						}

					}
				}

				if (valid)
				{
					res.push_back({ p, q });
				}

				//std::cout << "\n";

			}
		}
	}

	return clockwise(res, res.size());
}

std::vector<vec2f> ConvexHull(std::vector<vec2f> points)
{

	if (points.size() <= 3)
	{
		return points;
	}

	std::sort(points.begin(), points.end());

	//upper line

	std::vector<vec2f> up;

	up.push_back(points[0]);
	up.push_back(points[1]);

	for (int i = 2; i < points.size(); i++)
	{
		up.push_back(points[i]);

		int n = up.size();

		while (n > 2 && !isRightTurn(up[n - 3], up[n - 2], up[n - 1]))
		{
			auto temp = up[n - 1];

			up.pop_back();
			up.pop_back();

			up.push_back(temp);

			n--;

		}
	}

	//bottom line

	std::vector<vec2f> lw;

	lw.push_back(points[points.size() - 1]);
	lw.push_back(points[points.size() - 2]);

	for (int i = points.size() - 3; i >= 0; i--)
	{
		lw.push_back(points[i]);

		int n = lw.size();

		while (n > 2 && !isRightTurn(lw[n - 3], lw[n - 2], lw[n - 1]))
		{
			auto temp = lw[n - 1];

			lw.pop_back();
			lw.pop_back();

			lw.push_back(temp);

			n--;

		}

	}

	up.insert(up.end(), lw.begin() + 1, lw.end() - 1); // apend lw to up without repeating the first and the last points

	return up;
}
