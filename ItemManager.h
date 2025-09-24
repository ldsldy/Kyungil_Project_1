#pragma once
#include "Point.h"

class ItemManager
{
public:
	ItemManager() = default;
	//남은 토큰을 갯수를 알린다.
	inline const int GetTokenCount() const { return TokenCount; }
	//플레이어가 먹을 수 있다.

protected:
	Point ItemPos;
private:
	int TokenCount;
};

