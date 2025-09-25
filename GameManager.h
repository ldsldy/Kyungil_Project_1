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

	//���� ���� �Լ�
	void Run();

	//�÷��̾� ��ġ �ʱ�ȭ
	void InitGame();

	//����� �Լ�
	Point GetPlayerSpawnFromMM() const;
	Point GetCurrentPlayerPos() const;

private:
	Direction UserDirection = Direction::Default;
	Point CurrentPlayerPos;

	Player* CurrentPlayer;
	MapManager* CurrentMapManager;
	EnemyManager* CurrentEnemyManager;

	//�÷��̾� ���� ���� �Լ���
	bool CanPlayerMove(Direction InDirection);
	void PlayerMove();

	//�ٸ� Ŭ������ �����ؾ��ϴ� ���� ��� ������Ʈ
	void Update();
};

