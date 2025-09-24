#pragma once
#include "Player.h"
#include "MapManager.h"
#include "EnemyManager.h"
#include "ItemManager.h"

Player* UserPlayer;
MapManager* CurrentMapManager;
EnemyManager* CurrentEnemyManager;
ItemManager* CurrentItemManager;

class GameManager
{
public:
	GameManager()
	{
		UserPlayer = new Player;
		CurrentMapManager = new MapManager;
		CurrentEnemyManager = new EnemyManager;
		CurrentItemManager = new ItemManager;
	}
	~GameManager()
	{
		delete UserPlayer;
		delete CurrentMapManager;
		delete CurrentEnemyManager;
		delete CurrentItemManager;
	}

	//�ٸ� Ŭ������ �����ؾ��ϴ� ���� ��� ������Ʈ
	inline void Update()
	{
		UserDirection = UserPlayer->GetMoveDirection();
		UserPos = UserPlayer->GetPlayerPose();
	}
	//���� ���� �Լ�
	void Run();

	bool CanPlayerMove();
private:
	Direction UserDirection = Direction::Default;
	Point UserPos = 0;
	//��ū�� ������ �ʸŴ����� ���� �޾Ƽ� ����
	//�÷��̾ ��ū �浹�� �˸��� ����=>�ʸŴ������� �˸�
	//��ū�� 0�� �Ǹ� ���Ŵ������� �� ��ü�� �����϶�� �˸�

	//�÷��̾ ������ ȹ���� �˸� => ȹ���� �����ۿ� ���� �� �Ŵ������� �˸�
	//                            => �ʸŴ������� �˸�(������ ��ġ ����)
};

