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

	//다른 클래스와 공유해야하는 내용 계속 업데이트
	void Update();
	//게임 시작 함수
	void Run();

	bool CanPlayerMove();

	//플레이어 위치 초기화
	void InitGame();
private:
	Direction UserDirection = Direction::Default;
	Point UserPos = 0;

	Player* UserPlayer;
	MapManager* CurrentMapManager;
	EnemyManager* CurrentEnemyManager;
};

