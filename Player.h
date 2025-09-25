#pragma once
#include "Point.h"
#include "EnumClass.h"

extern class GameManager;

class Player
{
public:
	Player()
	{}

	//���� �Ŵ����� �÷��̾� ��ġ�� ��û�� ��
	inline Point GetPlayerPose() const { return PlayerPos; }
	
	//���� �浹(���ӿ��� or ü�°���)
	//������ ȹ��(�����ð� �� ��ü ������, �� ����) => ���ӸŴ����� �˸�
	Direction GetMoveDirection();

	void SetPosition(Point InPos) { PlayerPos = InPos; }

private:
	void Move(Direction MoveDirection);
	//Ű�� ������ �̵� (�̵� �ӵ� ����)

	/// <summary>
	/// �̵��� ������ �����ϴ� �Լ� => ���� �̵� �Լ��� ����
	/// </summary>
	/// <returns>�̵��� ������ Enum</returns>

	//���� ��ġ
	Point PlayerPos;
	int WalkSpeed;	//�̵� �ӵ�
	GameManager* CurrentGameManager;
};

