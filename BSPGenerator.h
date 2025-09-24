#pragma once
#include <vector>
#include <random>
#include "Map.h"
#include "Point.h"

using namespace std;

Map InMap; //전방 선언

//BSP노드 - 인덱스 기반 관리 유지 
struct BSPNode
{
	int x, y, Width, Height; //맵 좌표, 크기
	BSPNode* Left;
	BSPNode* Right;
	bool IsLeaf;

	BSPNode(int InX, int InY, int InWidth, int InHeight)
		:x(InX), y(InY), Width(InWidth), Height(InHeight), Left(nullptr), Right(nullptr), IsLeaf(true){}

	~BSPNode()
	{
		delete Left;
		delete Right;
	}
};

class BSPGenerator
{
public:
	BSPGenerator() : Root(nullptr), rng(random_device{}()) {}
	~BSPGenerator()
	{
		delete Root;
	}

	//Map 클래스에서 벡터를 받아 BSP 트리 생성 및 맵 생성
	void GenerateMap(Map& InMap, unsigned int MinRoomSize = 0);

private:
	BSPNode* Root;
	mt19937 rng;

	//BSP 트리 분할
	void SplitNode(BSPNode* InNode, unsigned int MinRoomSize);

	// 방 생성
	void CreateRooms(BSPNode* InNode, Map& InMap, unsigned int MinRoomSize);

	//복도 생성
	void CreateCorridors(BSPNode* InNode, Map& InMap);

	//두 방을 연결하는 복도 생성
	void ConnectRooms(const BSPNode* InRoom1, const BSPNode* InRoom2, Map& InMap);

	//구역의 중심점 찾기
	Point GetRoomCenter(const BSPNode* InNode) const;
};



