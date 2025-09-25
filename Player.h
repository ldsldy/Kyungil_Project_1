#pragma once
#include "Point.h"
#include "EnumClass.h"

extern class GameManager;

class Player
{
public:
	Player(){
		PlayerPos = (0, 0);
	}

	//���� �Ŵ����� �÷��̾� ��ġ�� ��û�� ��
	inline Point GetPlayerPose() const { return PlayerPos; }
	inline Point GetPlayerX() const { return PlayerPos.x; }
	inline Point GetPlayerY() const { return PlayerPos.y; }
	/// <summary>
	/// �̵��� ������ �����ϴ� �Լ� => ���� �̵� �Լ��� ����
	/// </summary>
	/// <returns>�̵��� ������ Enum</returns>
	Direction GetMoveDirection();

	inline void SetPositionX(int InX) { PlayerPos.x = InX; }
	inline void SetPositionY(int InY) { PlayerPos.y = InY; }
	inline void SetPosition(Point InPos) { PlayerPos = InPos; }

private:
	//���� ��ġ
	Point PlayerPos;
	int WalkSpeed;	//�̵� �ӵ�
	GameManager* CurrentGameManager;
};

