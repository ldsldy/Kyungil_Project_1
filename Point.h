#pragma once

struct Point
{
	int x, y;

	constexpr Point(int x = 0, int y = 0) :x(x), y(y) {}

	bool operator<(const Point& Other) const {
		if (x != Other.x)
			return x < Other.x;
		return y < Other.y;
	};

	inline bool operator==(const Point& Other) const
	{
		return x == Other.x && y == Other.y;
	}
	inline Point operator+(const Point& Other) const
	{
		return Point(x + Other.x, y + Other.y);
	}
	inline Point operator-(const Point& Other) const
	{
		return Point(x - Other.x, y - Other.y);
	}
	
};