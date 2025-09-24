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

	//�� �ʱ�ȭ(��� ���� ������ ����)
	void Init()
	{
		for(auto& row : MapData)
		{
			fill(row.begin(), row.end(), CellType::Wall);
		}
	}
	
private:
	//����
	//64*64 �� ������ ����
	//��, ���, (������, Ż�ⱸ) ��ġ ���� ����
	//Ư�� ��ǥ�� ��Ÿ�� Ȯ��/���� �޼���
	//�� ���� ���� ��� (isWall, isEmpty, hasItem)
	static const int MapSize = 64;
	static const int RegionSize = 8;
	static const int MaxNumRegions = (MapSize / RegionSize) * (MapSize / RegionSize); //64/8=8 -> 8*8=64 ����*����
	vector<vector<CellType>> MapData;
};

