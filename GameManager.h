#pragma once
#include"EnumClass.h"
#include"Point.h"

class Player;
class MapManager;
class EnemyManager;

class GameManager
{
public:
	GameManager();
	~GameManager();

	//�ٸ� Ŭ������ �����ؾ��ϴ� ���� ��� ������Ʈ
	void Update();
	//���� ���� �Լ�
	void Run();

	bool CanPlayerMove();

	//�÷��̾� ��ġ �ʱ�ȭ
	void InitGame();
private:
	Direction UserDirection = Direction::Default;
	Point UserPos = 0;

	Player* UserPlayer;
	MapManager* CurrentMapManager;
	EnemyManager* CurrentEnemyManager;
};

