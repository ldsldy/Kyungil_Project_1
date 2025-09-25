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

	//�� ������ ����
	inline CellType GetCellType(int InX, int InY) const
	{
		if (!IsValidPosition(InX, InY)) return CellType::Wall; //��ȿ���� ���� ��ǥ�� ������ ����
		return MapData[InY][InX];
	}
	//�� ������ ����(��, ���� �ƴ� ��쿡��)
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

	//�� �ʱ�ȭ(��� ���� ������ ����)
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

