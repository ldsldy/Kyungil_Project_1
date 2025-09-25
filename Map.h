#pragma once
#include "Point.h"
#include "EnumClass.h"
#include <iostream>
#include <vector>

using namespace std;

class Map
{
private:
	vector<vector<CellType>> MapData;
	vector<Point> RoomCenters; //�� �߽� ��ǥ ����
	int Width, Height;

public:
	Map(int InWidth=64, int InHeight=64);
	~Map() = default;

	//�� Ÿ�� �䱸
    CellType GetCell(int InX, int InY) const;
	//�� ����(��, ���� �ƴ� ��쿡��)
    void SetCell(int InX, int InY, CellType InType);
    
	//�� �� �ִ� ��ġ���� Ȯ��
	bool IsWalkable(int InX, int InY) const;
	//�� ������ Ȯ��
	bool IsValidPostion(int InX, int InY) const;
	bool IsWall(int InX, int InY) const;

	//�� ����, ���� ��ȯ
	inline int GetWidth() const {return Width};
	inline int GetHeight() const {return Height};

	// �� ����
	inline vector<Point> GetRoomCenters() const { return RoomCenters; }
	inline void AddRoomCenter(const Point& Center) { RoomCenters.push_back(Center); }
	inline void ClearRoomCenters() { RoomCenters.clear(); };

	//�ʱ�ȭ
	void Clear();

	//�� ���
	void Print(const Point& PlayerPos) const;
};

//inline bool IsValidPosition(int InX, int InY) const
//{
//	return InX >= 0 && InX < Width && InY >= 0 && InY < Height;
//}
//Ÿ�� ���� Ȯ��
//inline bool IsWall(int InX, int InY) const
//{
//	return GetCellType(InX, InY) == CellType::Wall;
//}
//inline bool IsFloor(int InX, int InY) const
//{
//	return GetCellType(InX, InY) == CellType::Floor;
//}
//inline bool IsExit(int InX, int InY) const
//{
//	return GetCellType(InX, InY) == CellType::Exit;
//}

	////�� �ʱ�ȭ(��� ���� ������ ����)
	//void Init()
	//{
	//	for (auto& row : MapCells)
	//	{
	//		fill(row.begin(), row.end(), CellType::Wall);
	//	}
	//}