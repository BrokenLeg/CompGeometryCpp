#include <iostream>
#include <vector>
#include <set>

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
		return sqrt( x*x + y*y );
	}
};

std::ostream& operator<<(std::ostream& os, const vec2f& v)
{
	std::cout << "( " << v.x << ", " << v.y << ")";

	return os;
}

bool left(const vec2f& a, const vec2f& b) // b is left to a
{
	return ( a.cross(b) > 0);
}

std::vector<vec2f> clockwise(std::vector<std::pair<vec2f, vec2f>> edges)
{

	if (edges.empty())
	{
		return {};
	}

	std::vector<vec2f> res;

	vec2f p = edges[0].first, q = edges[0].second;

	while (res.size() < edges.size())
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

std::vector<vec2f> ConvexHull(std::vector<vec2f> points)
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

				std::cout << p << ", " << q << "\n";

				for (auto r : points)
				{
					if (r != p && r != q)
					{

						std::cout << r;

						if (left(l, r - q))
						{

							std::cout << " -\n";

							valid = false;
						}
						else
						{
							std::cout << " +\n"; //right
						}
						
					}
				}

				if (valid)
				{
					res.push_back({p, q});
				}

				std::cout << "\n";

			}
		}
	}

	return clockwise(res);
}

int main()
{

	vec2f a(1, 1), b(2, 3), c(3, 1), d(4, 3), e(2, 2);

	std::vector<vec2f> res = ConvexHull({a, b, c, d, e});

	for (auto p : res)
	{
		std::cout << p << " ";
	}

	return 0;
}