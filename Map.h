#pragma once
#include "EnumClass.h"
#include <vector>

#include <iostream>
using namespace std;

class Map
{
public:
	Map() 
	{
		MapData.resize(MapLength, vector<CellType>(MapLength, CellType::Wall));
	}
	~Map() = default;

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
	inline bool IsFloor(int InX, int InY) const
	{
		return GetCellType(InX, InY) == CellType::Floor;
	}
	inline bool IsExit(int InX, int InY) const
	{
		return GetCellType(InX, InY) == CellType::Exit;
	}
	inline bool IsValidPosition(int InX, int InY) const
	{
		return InX >= 0 && InX < MapLength && InY >= 0 && InY < MapLength;
	}

	inline int GetMapLength() const { return MapLength; }

	//맵 초기화(모든 셀을 벽으로 설정)
	void Init()
	{
		for(auto& row : MapData)
		{
			fill(row.begin(), row.end(), CellType::Wall);
		}
	}
	
private:
	static const int MapLength = 64;
	vector<vector<CellType>> MapData;
};

