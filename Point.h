#pragma once

struct Point
{
	int x, y;

	constexpr Point(int x = 0, int y = 0) :x(x), y(y) {}

	inline bool operator==(const Point& other) const
	{
		return x == other.x && y == other.y;
	}
};