#pragma once
#include <vector>
#include <memory>
#include <random>
#include "Point.h"

using namespace std;

extern class Map;

struct Room
{
	int x, y;
	int Width, Height;

	Room() : x(0), y(0), Width(0), Height(0) {}
	Room(int InX, int InY, int InWidth, int InHeight)
		:x(InX), y(InY), Width(InWidth), Height(InHeight) {}

	inline Point GetCenter() const
	{
		return Point(x + Width / 2, y + Height / 2);
	}

	inline bool IsValid() const
	{
		return Width > 0 && Height > 0;
	}
};

//BSP노드 - 인덱스 기반 관리 유지 
struct BSPNode
{
	int x, y, Width, Height; //맵 좌표, 크기
	BSPNode* Left;
	BSPNode* Right;
	bool IsLeaf;
	Room ContainedRoom;

	BSPNode(int InX, int InY, int InWidth, int InHeight)
		:x(InX), y(InY), Width(InWidth), Height(InHeight), Left(nullptr), Right(nullptr), IsLeaf(true){}

	inline Point GetRoomCenter() const 
	{
		//리프 노드이고 방이 유효하면 방 중심점 반환
		if (IsLeaf && ContainedRoom.IsValid())
		{
			return ContainedRoom.GetCenter();
		}
		//리프 노드가 아니면 자식 노드에서 방 중심점 찾기
		else if (!IsLeaf)
		{
			if (Left && Left->GetRoomCenter().x != 0)
				return Left->GetRoomCenter();
			if (Right && Right->GetRoomCenter().x !=0)
				return Right->GetRoomCenter();
		}
		//리프 노드이지만 방이 없다.
		return Point(0, 0);
	}
};

class BSPGenerator
{
public:
	BSPGenerator() :Root(nullptr), rng(random_device{}()) {}
	~BSPGenerator()
	{
		delete Root;
	}

	//Map 클래스에서 벡터를 받아 BSP 트리 생성 및 맵 생성
	void GenerateMap(Map& InMap, unsigned int MinRoomSize = 6);

private:
	BSPNode* Root;
	mt19937 rng;
	bool bIsInitialized;

	//BSP 트리 분할
	void SplitNode(BSPNode* InNode, unsigned int MinRoomSize);

	// 방 생성
	void CreateRooms(BSPNode* InNode, Map& InMap, unsigned int MinRoomSize);

	//복도 생성
	void CreateCorridors(BSPNode* InNode, Map& InMap);

	//두 방을 연결하는 복도 생성
	void ConnectRooms(const BSPNode* InRoom1, const BSPNode* InRoom2, Map& InMap);

	void PrintBSPRooms(const BSPNode* InNode);

	Map* InMap;
};


