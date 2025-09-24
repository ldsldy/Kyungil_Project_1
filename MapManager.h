#pragma once
#include "BSPGenerator.h"
#include "GameManger.h"
#include "Map.h"

//포인터 변수만 선언
GameManager* CurrentGameManager;
BSPGenerator* BSPGen;

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

		//BSPGenerator로 Map 맵 구조 변경
	}

	//GameManager에서 Map정보와 함수를 얻기 위함
	Map* GetMap() { return CurrentMap; }

private:
	//BSP알고리즘을 통한 맵 분할 및 합치기
	//분할된 구역에 토큰 배치 위치 생성
	//플레이어 랜덤 스폰 위치 결정
	//BFS를 이용한 경로 탐색 및 최장거리 계산
	//탈출구 자동 배치
	//맵 전체 프로세스 관리
	//토큰 관리(게임매니저에게 토큰에 대한 정보를 받아 토큰 제거)

	//맵 출력(디버그용)
	void PrintTestMap() const;

	//맵의 한 부분 출력(디버그용)
	void PrintRegionMap() const;

	int MapLength;
	int RegionSize;
	int TokenCount;

	Map* CurrentMap;
};

