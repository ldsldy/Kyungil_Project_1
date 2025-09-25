#pragma once
#include "Point.h"
#include <iostream>
#include <vector>

using namespace std;

enum class CellType
{
	Wall,
	Floor,
	Token,
	Enemy,
	Player,
	Exit
};

class Map
{
private:
	vector<vector<CellType>> MapData;
	vector<Point> RoomCenters; //�� �߽� ��ǥ ����
	int Width, Height;

public:
	Map(int InWidth, int InHeight);
	~Map() = default;

    TileType getTile(int x, int y) const;
    void setTile(int x, int y, TileType type);
    bool isWalkable(int x, int y) const;

    int getWidth() const;
    int getHeight() const;
	//�� ����(��, ���� �ƴ� ��쿡��)
	void SetCell(int InX, int InY, CellType Type);
	//�� Ÿ�� �䱸
	CellType GetCell(int InX, int InY) const;
	//�� �� �ִ� ��ġ���� Ȯ��
	bool IsWalkable(int InX, int InY) const;

	//�� ����, ���� ��ȯ
	int GetWidth() const { return Width; }
	int GetHeight() const { return Height; }

	// �� ����
	vector<Point> GetRoomCenters() const;
	void AddRoomCenter(const Point& Center);
	void ClearRoomCenters();
};


    std::vector<std::pair<int, int>> getRoomCenters() const;

protected:
    std::vector<std::vector<TileType>> grid;
    std::vector<std::pair<int, int>> roomCenters;
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