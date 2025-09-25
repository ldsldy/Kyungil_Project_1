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
	Enemy GameEnemy;

	vector<Point> TokenPositions;
	Point ExitPosition;
	bool IsExitOpen;
	GameState CurrentGameState;

	int TotalTokens;	// ��ū�� �ΰ��� ���� ����
	//int CollectedTokens;
public:
	GameManager();
	~GameManager() = default;

	//���� ���� �Լ�
	void Run();

	//�÷��̾� ��ġ �ʱ�ȭ
	void Init();

	//�÷��̾� �̵�, �� �̵�, ��ū ȹ��, ���� ���� ������Ʈ
	void Update();

	//�� ���
	void Print();

	// ������ �浹 üũ
	bool IsContactEnemy();

	void CheckGameProgress();

	inline bool IsAllTokensCollected() const { return TotalTokens == 0; }
};

