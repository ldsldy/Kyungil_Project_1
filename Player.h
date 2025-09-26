#pragma once
#include "Point.h"
#include "EnumClass.h"

class Map;

class Player
{
private:
	//�÷��̾� ��ġ
	Point Position;

public:
	Player():Position(0,0){}

	inline const Point GetPosition() const { return Position; }
	inline void SetPosition(const Point& InPos) { Position = InPos; }
	
	// <summary>
	/// �÷��̾��� �̵� ������ �Է¹޾� ��ȯ�ϴ� �Լ�
	/// </summary>
	/// <returns>�̵��� ������ Enum</returns>
	Direction GetInputDirection();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="InDirection"></param>
	/// <param name="InMap"></param>
	/// <returns></returns>
	bool Move(Direction InDirection, Map& InMap);

	bool DetectedTokenCollision(Map& InMap);
};

//�ڱ� ��ġ�� �ʿ� �Ѹ���
//�̵� ������ �Է¹޾� �̵�
//��ū �浹 ����
//�ⱸ �浹 ����
