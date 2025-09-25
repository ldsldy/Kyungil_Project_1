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

	int TotalTokens;	// 토큰을 두개로 나눈 이유
	//int CollectedTokens;
public:
	GameManager();
	~GameManager() = default;

	//게임 시작 함수
	void Run();

	//플레이어 위치 초기화
	void Init();

	//플레이어 이동, 적 이동, 토큰 획득, 게임 상태 업데이트
	void Update();

	//맵 출력
	void Print();

	// 적과의 충돌 체크
	bool IsContactEnemy();

	void CheckGameProgress();

	inline bool IsAllTokensCollected() const { return TotalTokens == 0; }
};

