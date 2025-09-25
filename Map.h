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
	vector<Point> RoomCenters; //방 중심 좌표 저장
	int Width, Height;

public:
	Map(int InWidth, int InHeight);
	~Map() = default;

    CellType getTile(int x, int y) const;
    void SetTile(int x, int y, CellType type);
    bool IsWalkable(int x, int y) const;

    int GetWidth() const;
    int GetHeight() const;
	//셀 설정(단, 벽이 아닐 경우에만)
	void SetCell(int InX, int InY, CellType Type);
	//셀 타입 요구
	CellType GetCell(int InX, int InY) const;
	//갈 수 있는 위치인지 확인
	bool IsWalkable(int InX, int InY) const;

	//맵 가로, 세로 반환
	int GetWidth() const { return Width; }
	int GetHeight() const { return Height; }

	// 방 정보
	vector<Point> GetRoomCenters() const;
	void AddRoomCenter(const Point& Center);
	void ClearRoomCenters();
};


    vector<Point> GetRoomCenters() const;

protected:
    std::vector<std::vector<TileType>> grid;
    vector<std::pair<int, int>> roomCenters;
};

//inline bool IsValidPosition(int InX, int InY) const
//{
//	return InX >= 0 && InX < Width && InY >= 0 && InY < Height;
//}
//타일 상태 확인
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

	////맵 초기화(모든 셀을 벽으로 설정)
	//void Init()
	//{
	//	for (auto& row : MapCells)
	//	{
	//		fill(row.begin(), row.end(), CellType::Wall);
	//	}
	//}