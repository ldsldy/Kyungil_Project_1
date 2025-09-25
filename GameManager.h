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

	//게임 시작 함수
	void Run();

	//플레이어 위치 초기화
	void InitGame();

	//맵출력 함수
	Point GetPlayerSpawnFromMM() const;
	Point GetCurrentPlayerPos() const;

private:
	Direction UserDirection = Direction::Default;
	Point CurrentPlayerPos;

	Player* CurrentPlayer;
	MapManager* CurrentMapManager;
	EnemyManager* CurrentEnemyManager;

	//플레이어 실제 조작 함수들
	bool CanPlayerMove(Direction InDirection);
	void PlayerMove();

	//다른 클래스와 공유해야하는 내용 계속 업데이트
	void Update();
};

