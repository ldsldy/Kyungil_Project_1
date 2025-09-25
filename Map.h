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
		MapCells.resize(MapLength, vector<CellType>(MapLength, CellType::Wall));
	}
	virtual ~Map() = default;

	
	//맵 데이터 설정(단, 벽이 아닐 경우에만)
	inline void SetCellType(int InX, int InY, CellType Type)
	{
		if (IsValidPosition(InX, InY)) {
			MapCells[InY][InX] = Type;
		}
	}
	//맵 초기화(모든 셀을 벽으로 설정)
	virtual void Init()
	{
		for (auto& row : MapCells)
		{
			fill(row.begin(), row.end(), CellType::Wall);
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
	//맵 데이터 요구
	inline CellType GetCellType(int InX, int InY) const
	{
		if (!IsValidPosition(InX, InY)) return CellType::Wall; //유효하지 않은 좌표는 벽으로 간주
		return MapCells[InY][InX];
	}
	
protected:
	static const int MapLength = 64;
	vector<vector<CellType>> MapCells;
};

