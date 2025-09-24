#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include "Map.h"
#include "Point.h"
using namespace std;

// map -> bsp -> mapmanager -> game manager
Map InMap; //전방 선언

struct Room
{
	int x, y;
	int Width, Height;
	int RegionX, RegionY;

	Room() = default;
	Room(int x, int y, int width, int height, int regX=255, int regY=255)
		:x(x), y(y), Width(width), Height(height), RegionX(regX), RegionY(regY) {}

	//방의 중심 좌표 반환
	inline Point GetCenter() const
	{
		return Point(x + Width / 2, y + Height / 2);
	}

	//방 안에 좌표가 포함되는지 검사
	inline bool IsInside(int px, int py) const
	{
		return px >= x && px < x + Width && py >= y && py < y + Height;
	}
};

//BSP노드 - 인덱스 기반 관리 유지 
struct BSPNode
{
public:
	int x, y, Width, Height; //맵 좌표, 크기
	int regionX, regionY; // 5*5 구역 안에서의 좌표
	int LeftChild;	//벡터 인덱스 -1이면 null
	int RightChild; //벡터 인덱스 -1이면 null
	int RoomCount; //이 노드가 포함하는 방의 개수

	BSPNode() :LeftChild(-1), RightChild(-1), RoomCount(0) {}
	BSPNode(int x, int y, int width, int height)
		:x(x), y(y), Width(width), Height(height), LeftChild(-1), RightChild(-1), RoomCount(0) {
	}

	//너무 작아서 쪼갤 수 없는지 검사
	inline bool CanSplit() const
	{
		return Width >= 10 || Height >= 10;
	}
	//리프 노드인지 검사
	inline bool IsLeaf() const
	{
		return LeftChild == -1 && RightChild == -1;
	}
};

class BSPGenerator
{
private:
	vector<BSPNode> Nodes;
	vector<Room> Rooms;
	int rngState; //빠른 랜덤 생성을 위한 상태 변수

	int MapSize;
	int RegionSize;
	int NumRegions;
	int MaxTotalRooms;
	int MaxBSPNodes;

	//빠른 랜덤 생성 함수(LCG)
	inline int FastRandom()
	{
		rngState = rngState * 1664525U + 1013904223U;
		return rngState;
	}

	//0부터 max-1까지의 랜덤 정수 반환
	inline int FastRandomRange(int max)
	{
		return FastRandom() % max;
	}

	//새 노드 할당
	inline int AllocateNode(int x, int y, int w, int h)
	{
		//새 노드 생성
		Nodes.emplace_back(x, y, w, h);
		return static_cast<int>(Nodes.size() - 1);
	}

	//새 방 할당
	inline void AllocateRoom(int x, int y, int w, int h, int regX, int regY)
	{
		Rooms.emplace_back(x, y, w, h, regX, regY);
	}

	/// <summary>
	/// 방 생성 - 노드 내의 각 구역에 대해 방 생성 시도
	/// </summary>
	/// <param name="NodeIndex"></param>
	void CreateRoomsInNode(int NodeIndex);

	/// <summary>
	/// 특정 구역에 방 생성
	/// 방 크기와 위치는 구역 내에서 랜덤 결정
	/// </summary>
	/// <param name="node">기준	이 되는 BSP노드</param>
	/// <param name="regX">몇 번째 구역</param>
	/// <param name="regY">몇 번째 구역</param>
	void CreateRoomInRegion(const BSPNode& node, int regX, int regY);

	/// <summary>
	/// BSP 트리 생성
	/// </summary>
	/// <param name="RegX"></param>
	/// <param name="RegY"></param>
	/// <returns></returns>
	const Room* FindRoomInRegion(int RegX, int RegY) const;

	/// <summary>
	/// 두 방을 연결하는 통로 생성
	/// </summary>
	/// <param name="InMap">정보를 기록할 맵</param>
	/// <param name="InRoom1">연결할 방 1</param>
	/// <param name="InRoom2">연결될 방 2</param>
	void ConnectRooms(Map& InMap, const Room& InRoom1, const Room& InRoom2);

	/// <summary>
	/// 두 좌표를 연결하는 통로 생성
	/// </summary>
	/// <param name="InMap">통로를 생성할 맵</param>
	/// <param name="x1">좌표1의 x값</param>
	/// <param name="y1">좌표1의 y값</param>
	/// <param name="x2">좌표2의 x값</param>
	/// <param name="y2">좌표2의 y값</param>
	void CreateCorridors(Map& InMap, int x1, int y1, int x2, int y2);

	/// <summary>
	/// 맵 정보 캐싱
	/// </summary>
	/// <param name="InMap">정보를 받아올 맵</param>
	void CacheMapInfo(const Map& InMap);

	//void DrawRooms(Map& map) const;

public:
	/// <summary>
	/// 두 방 사이의 거리 계산 함수
	/// </summary>
	float GetDistanceBetweenRooms(const Room& room1, const Room& room2) const;

	/// <summary>
	/// 모든 방의 중심점 좌표를 벡터 형태로 반환
	/// </summary>
	vector<Point> GetAllRoomCenters() const;

};
