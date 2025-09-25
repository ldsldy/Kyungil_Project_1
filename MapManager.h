#pragma once
#include "BSPGenerator.h"
#include "GameManager.h"
#include "Map.h"

#include <iostream>

using namespace std;

extern class Map;
extern class BSPGenerator;

//알고리즘과 로직 처리에 집중
class MapManager
{
private:
	//분할된 구역에 토큰 배치 위치 생성
	//플레이어 랜덤 스폰 위치 결정
	//BFS를 이용한 경로 탐색 및 최장거리 계산
	//탈출구 자동 배치
	//토큰 관리(게임매니저에게 토큰에 대한 정보를 받아 토큰 제거)
	Map* ManagerMap;
	BSPGenerator* BSPGen;
	int MapLength;
	int MapManagerToken; //맵에 설치된 토큰 갯수
	
	inline Point GetPlayer() const { return BSPGen->GetPlayerSpawn(); }

public:
	MapManager() : ManagerMap(new Map), BSPGen(new BSPGenerator)
	{
		cout << "MapManager Constructed\n";
		MapLength = ManagerMap->GetMapLength();
		BSPGen->GenerateMap(*ManagerMap, 10);
	}
	~MapManager()
	{
		delete ManagerMap;
		delete BSPGen;
		cout << "MapManager Destructed\n";
	}
	
	//BSP에서 플레이어 스폰 위치를 받아와 Map에 반영
	void PlayerSpawnPoint();
	
	//GameManager에서 Map정보와 함수를 얻기 위함
	Map* GetMap() { return ManagerMap;}

	//맵출력 함수
	void PrintMap() const;

	//=======디버깅============//
	void PrintMapInfo() const;
};

