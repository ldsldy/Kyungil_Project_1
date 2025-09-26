#pragma once
#include "Map.h"
#include "BSPGenerator.h"
#include "Player.h"
#include "Enemy.h"
#include "EnumClass.h"
#include "Point.h"
#include <vector>


class GameManager
{
private:
	Map GameMap;
	BSPGenerator GameMapGenerator;
	Player GamePlayer;
	vector<Enemy> GameEnemies;
	vector<Point> TokenPositions;
	
	Point ExitPosition;
	bool IsExitOpen;
	GameState CurrentGameState;

	int TotalTokens;
	int MaxEnemies = 3;

	static constexpr int MapWidth = 64;
	static constexpr int MapHeighth = 64;
	bool IsDebugMode;
public:
	GameManager();
	~GameManager() = default;

	//���� ���� �Լ�
	void Run();

private:
	//�÷��̾� ��ġ �ʱ�ȭ
	void Init();

	//�÷��̾� �̵�, �� �̵�, ��ū ȹ��, ���� ���� ������Ʈ
	void Update();

	//�� ���
	void Print();

	void SpawnEnemies();

	// ������ �浹 üũ
	bool IsConllisionEnemies();

	inline bool IsAllTokensCollected() const { return TotalTokens == 0; }

	void CashingRoomCentersToEnemy(Enemy& InEnemy);
};

