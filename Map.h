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
	vector<Point> RoomCenters; //방 중심 좌표 저장
	int Width, Height;

public:
	Map(int InWidth=64, int InHeight=64);
	~Map() = default;

	//셀 타입 요구
    CellType GetCell(int InX, int InY) const;
	//셀 설정(단, 벽이 아닐 경우에만)
    void SetCell(int InX, int InY, CellType InType);
    
	//갈 수 있는 위치인지 확인
	bool IsWalkable(int InX, int InY) const;
	
	//맵 안인지 확인
	bool IsValidPosition(int InX, int InY) const;

	//벽인지 확인
	bool IsWall(int InX, int InY) const;

	//맵 가로, 세로 반환
	inline int GetWidth() const { return Width; }
	inline int GetHeight() const { return Height; }

	// 방 정보
	inline vector<Point> GetRoomCenters() const { return RoomCenters; }
	inline void AddRoomCenter(const Point& Center) { RoomCenters.push_back(Center); }
	inline void ClearRoomCenters() { RoomCenters.clear(); };

	//초기화
	void Clear();

	//맵 출력
	void Print(const Point& PlayerPos) const;
	void PrintDarkMode(const Point& PlayerPos) const;
};