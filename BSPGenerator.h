#pragma once
#include "Map.h"
#include <random>


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

	inline Point GetRandomPoint(mt19937 InRng) const
	{
		int RandX = x+1 + (InRng() % Width-2);
		int RandY = y+1 + (InRng() % Height-2);
		return Point(RandX, RandY);
	}
};

struct BSPNode
{
	int x, y, Width, Height; //맵 좌표, 크기
	BSPNode* Left;
	BSPNode* Right;
	bool IsLeaf;
	Room ContainedRoom;

	BSPNode(int InX, int InY, int InWidth, int InHeight)
		:x(InX), y(InY), Width(InWidth), Height(InHeight), Left(nullptr), Right(nullptr), IsLeaf(true){}

	~BSPNode()
	{
		delete Left;
		delete Right;
	}

	Point GetRoomCenter() const
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

class BSPGenerator:public Map
{
private:
	mt19937 rng;
	BSPNode* Root;
	vector<Room> LeafRooms;

public:
	BSPGenerator() : rng(random_device{}()), Root(nullptr) { }
	~BSPGenerator(){ delete Root; }

	//Map 클래스에서 벡터를 받아 BSP 트리 생성 및 맵 생성
	void GenerateMap(Map& InMap, unsigned int MinRoomSize = 10, int MaxDepth = 5);

	//플레이어 시작 위치는 첫번쨰 리프 노드 방의 중심
	Point GetPlayerSpawn() const;
	vector<Point> GetTokenSpawns(int InCount) const;
	vector<Point> GetEnemiesSpawn(int InCount) const;
	Point GetExitSpawn() const;

private:
	//BSP 트리 분할
	// InNode: 분할할 노드, MinRoomSize: 방의 최소 크기, InDepth: 현재 깊이, MaxDepth: 최대 깊이
	void SplitNode(BSPNode* InNode, unsigned int MinRoomSize, int InDepth, int MaxDepth);

	// 방 생성
	void CreateRooms(BSPNode* InNode, Map& InMap, unsigned int MinRoomSize);

	//복도 생성
	void CreateCorridors(BSPNode* InNodes, Map& InMap);

	//두 방을 연결하는 복도 생성
	// InCenter1, InCenter2: 연결할 두 방의 노드
	void ConnectRooms(const Point& InCenter1, const Point& InCenter2, Map& InMap);

	////방의 좌표를 전부 출력(디버깅용)
	//void PrintBSPRooms(const BSPNode* InNode);
};


