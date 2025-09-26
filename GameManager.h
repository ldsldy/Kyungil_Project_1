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

	//게임 시작 함수
	void Run();

private:
	//플레이어 위치 초기화
	void Init();

	//플레이어 이동, 적 이동, 토큰 획득, 게임 상태 업데이트
	void Update();

	//맵 출력
	void Print();

	void SpawnEnemies();

	// 적과의 충돌 체크
	bool IsConllisionEnemies();

	inline bool IsAllTokensCollected() const { return TotalTokens == 0; }

	void CashingRoomCentersToEnemy(Enemy& InEnemy);
};

