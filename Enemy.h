#pragma once
#include "Point.h"
#include <vector>
#include <queue>

using namespace std;

class Map;

class Enemy
{
private:
	Point Position;

	vector<Point> BFSFindPath(const Point& InStart, const Point& InTarget, Map& InMap);
	

public:
	Enemy() :Position(0, 0) {}

	inline Point GetPosition() const { return Position; } const
	inline void SetPosition(const Point& InPos) { Position = InPos; }

	void Update(const Point& InPlayerPos, Map& InMap);
};

//���� ����(�⺻, ��ū�� �� ������� �� ��ü) <= �߰� 
//�÷��̾�� �޸��Ⱑ ���Ƽ� �ѹ� �����ϸ� ��� �����ϴ� ���� ���� �����̸� ��� �޽�	<= �߰�
//�� �߰�(�÷��̾ ������ ������ ������? ��� ��)�� ���� �̵�(�÷��̾� ��ġ)
//ĭ���� �����ϸ� �ʹ� �δ�Ǵ� �÷��̾ ���� ���� �ȿ� �ִ����� üũ�ϰ�
//���� �ð����� �ٽ� ������Ʈ

//��� ǥ�� ����� ���
