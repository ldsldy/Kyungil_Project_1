#pragma once
#include "Point.h"
#include "EnumClass.h"
#include "GameManger.h"

GameManager* CurrentGameManager;

class Player
{
public:
	Player()
	{
		//���� �Ŵ������Լ� �� �Ŵ����� ������ �÷��̾� ���� ��ġ�� �޾ƿͼ� �ʱ�ȭ
	}

	//���� �Ŵ����� �÷��̾� ��ġ�� ��û�� ��
	inline Point GetPlayerPose() const { return PlayerPos; }
	

	//���� �浹(���ӿ��� or ü�°���)
	//������ ȹ��(�����ð� �� ��ü ������, �� ����) => ���ӸŴ����� �˸�
	Direction GetMoveDirection();

private:
	void Move(Direction MoveDirection);
	//Ű�� ������ �̵� (�̵� �ӵ� ����)

	/// <summary>
	/// �̵��� ������ �����ϴ� �Լ� => ���� �̵� �Լ��� ����
	/// </summary>
	/// <returns>�̵��� ������ Enum</returns>

	//���� ��ġ
	Point PlayerPos;
	int WalkSpeed; //�̵� �ӵ�
};

