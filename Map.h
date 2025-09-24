#pragma once
#include "EnumClass.h"
#include <vector>

using namespace std;

class Map
{
public:
	Map() 
	{
		MapData.resize(MapSize, vector<CellType>(MapSize, CellType::Wall));
	}

	//맵 데이터 접근
	inline CellType GetCellType(int InX, int InY) const
	{
		if (!IsValidPosition(InX, InY)) return CellType::Wall; //유효하지 않은 좌표는 벽으로 간주
		return MapData[InY][InX];
	}
	//맵 데이터 설정(단, 벽이 아닐 경우에만)
	inline void SetCellType(int InX, int InY, CellType Type)
	{
		if (IsValidPosition(InX, InY)) {
			MapData[InY][InX] = Type;
		}
	}

	inline bool IsWall(int InX, int InY) const
	{
		return GetCellType(InX, InY) == CellType::Wall;
	}
	inline bool IsEmpty(int InX, int InY) const
	{
		return GetCellType(InX, InY) == CellType::Floor;
	}
	inline bool HasItem(int InX, int InY) const
	{
		return GetCellType(InX, InY) == CellType::Item;
	}
	inline bool IsExit(int InX, int InY) const
	{
		return GetCellType(InX, InY) == CellType::Exit;
	}
	inline bool IsValidPosition(int InX, int InY) const
	{
		return InX >= 0 && InX < MapSize && InY >= 0 && InY < MapSize;
	}

	inline int GetMapSize() const { return MapSize; }
	inline int GetRegionSize() const { return RegionSize; }
	inline int GetMaxNumRegions() const { return MaxNumRegions; }

	//맵 초기화(모든 셀을 벽으로 설정)
	void Init()
	{
		for(auto& row : MapData)
		{
			fill(row.begin(), row.end(), CellType::Wall);
		}
	}
	
private:
	//변수
	//64*64 맵 데이터 저장
	//벽, 통로, (아이템, 탈출구) 위치 정보 보관
	//특정 좌표의 셀타입 확인/설정 메서드
	//맵 상태 조희 기능 (isWall, isEmpty, hasItem)
	static const int MapSize = 64;
	static const int RegionSize = 8;
	static const int MaxNumRegions = (MapSize / RegionSize) * (MapSize / RegionSize); //64/8=8 -> 8*8=64 가로*세로
	vector<vector<CellType>> MapData;
};

