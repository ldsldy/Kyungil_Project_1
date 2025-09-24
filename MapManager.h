#pragma once
#include "BSPGenerator.h"
#include "GameManager.h"
#include "Map.h"

//알고리즘과 로직 처리에 집중
class MapManager
{
public:
	MapManager()
	{
		CurrentMap = new Map();
		//자주 사용하고 메모리를 적게 먹는 데이터 캐싱
		MapLength = CurrentMap->GetMapLength();
		RegionSize = CurrentMap->GetRegionSize();
		MapManagerToken = 0;
	}
	~MapManager()
	{
		delete CurrentMap;
		delete BSPGen;
	}

	//맵 생성
	void GenerateMap(unsigned int MinRoomSize = 6);
	
	//GameManager에서 Map정보와 함수를 얻기 위함
	Map* GetMap() { return CurrentMap; }

	//맵출력 함수
	void PrintMap() const;



	//=======디버깅============//
	//맵 출력(디버그용)
	void PrintTestMap() const;

	//맵의 한 부분 출력(디버그용)
	void PrintRegionMap() const;

	void PrintMapInfo() const;

private:
	//분할된 구역에 토큰 배치 위치 생성
	//플레이어 랜덤 스폰 위치 결정
	//BFS를 이용한 경로 탐색 및 최장거리 계산
	//탈출구 자동 배치
	//토큰 관리(게임매니저에게 토큰에 대한 정보를 받아 토큰 제거)

	

	int MapLength;
	int RegionSize;
	int MapManagerToken; //맵에 설치된 토큰 갯수

	Map* CurrentMap;
	BSPGenerator* BSPGen;
};

