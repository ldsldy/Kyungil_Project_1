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
		return GetCellType(InX, InY) == CellType::Empty;
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
		return InX >= 0 && InX < Width && InY >= 0 && InY < Height;
	}

	inline int GetWidth() const { return MapSize; }
	inline int GetHeight() const { return MapSize; }

	//�� �ʱ�ȭ(��� ���� ������ ����)
	void Init()
	{
		for(auto& row : MapData)
		{
			fill(row.begin(), row.end(), CellType::Wall);
		}
	}

	//�� ���(����׿�)
	void PrintTestMap() const;

	//���� �� �κ� ���(����׿�)
	void PrintRegionMap() const;
	
private:
	//����
	//25*25 �� ������ ����
	//��, ���, (������, Ż�ⱸ) ��ġ ���� ����
	//Ư�� ��ǥ�� ��Ÿ�� Ȯ��/���� �޼���
	//�� ���� ���� ��� (isWall, isEmpty, hasItem)
	static const int MapSize = 25;
	static const int RegionSize = 5;
	vector<vector<CellType>> MapData;
};

