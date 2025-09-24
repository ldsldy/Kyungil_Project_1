#pragma once
#include"EnumClass.h"
#include"Point.h"

extern class Player;
extern class MapManager;
extern class EnemyManager;
extern class ItemManager;

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
private:
	Direction UserDirection = Direction::Default;
	Point UserPos = 0;
	//토큰의 갯수를 맵매니저로 부터 받아서 관리
	//플레이어가 토큰 충돌을 알릴때 제거=>맵매니저에게 알림
	//토큰이 0이 되면 적매니저에게 맵 전체를 추적하라고 알림

	//플레이어가 아이템 획득을 알림 => 획득한 아이템에 따라 적 매니저에게 알림
	//                            => 맵매니저에게 알림(아이템 위치 제거)
	Player* UserPlayer;
	MapManager* CurrentMapManager;
	EnemyManager* CurrentEnemyManager;
	ItemManager* CurrentItemManager;
};

