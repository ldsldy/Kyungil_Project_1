#pragma once
#include "Point.h"

class ItemManager
{
public:
	ItemManager() = default;
	//���� ��ū�� ������ �˸���.
	inline const int GetTokenCount() const { return TokenCount; }
	//�÷��̾ ���� �� �ִ�.

protected:
	Point ItemPos;
private:
	int TokenCount;
};

