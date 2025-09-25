#pragma once
#include "Map.h"
#include <random>
//#include <memory>


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
	
	//bool operator==(const Room& Other) const
	//{
	//	if (x == Other.x && y == Other.y)
	//		return true;
	//	return false;
	//}
};

//BSP��� - �ε��� ��� ���� ���� 
struct BSPNode
{
	int x, y, Width, Height; //�� ��ǥ, ũ��
	BSPNode* Left;
	BSPNode* Right;
	bool IsLeaf;
	Room ContainedRoom;

	BSPNode(int InX, int InY, int InWidth, int InHeight)
		:x(InX), y(InY), Width(InWidth), Height(InHeight), Left(nullptr), Right(nullptr), IsLeaf(true){}

	//inline Point GetRoomCenter() const 
	//{
	//	//���� ����̰� ���� ��ȿ�ϸ� �� �߽��� ��ȯ
	//	if (IsLeaf && ContainedRoom.IsValid())
	//	{
	//		return ContainedRoom.GetCenter();
	//	}
	//	//���� ��尡 �ƴϸ� �ڽ� ��忡�� �� �߽��� ã��
	//	else if (!IsLeaf)
	//	{
	//		if (Left && Left->GetRoomCenter().x != 0)
	//			return Left->GetRoomCenter();
	//		if (Right && Right->GetRoomCenter().x !=0)
	//			return Right->GetRoomCenter();
	//	}
	//	//���� ��������� ���� ����.
	//	return Point(0, 0);
	//}
};

class BSPGenerator:public Map
{
private:
	mt19937 rng;

protected:
	BSPNode* Root;
	vector<Room> LeafRooms;
	Point PlayerSpawn;
	//Point ExitPoint;
	//vector<Point> EnemySpawnPositions;
	//vector<Point> TokenSpawnPositions;

public:
	BSPGenerator() : rng(random_device{}()) {}
	~BSPGenerator()
	{
		delete Root;
		cout << "BSP Destructed\n";
	}

	//Map Ŭ�������� ���͸� �޾� BSP Ʈ�� ���� �� �� ����
	void GenerateMap(Map& InMap, unsigned int MinRoomSize = 10, int MaxDepth = 5);

	inline Point GetPlayerSpawn() const { return PlayerSpawn; }

protected:
	//BSP Ʈ�� ����
	void SplitNode(BSPNode* InNode, unsigned int MinRoomSize);

	// �� ����
	void CreateRooms(BSPNode* InNode, unsigned int MinRoomSize);

	//���� ����
	void CreateCorridors(BSPNode* InNodes);

	////�� ���� �����ϴ� ���� ����
	//void ConnectRooms(const BSPNode* InRoom1, const BSPNode* InRoom2);

	////���� ����� ����� ���Ϳ� ����
	//void GetLeafRoomsVector(vector<Room>& InLeafRooms);

	////���� ��ǥ�� ���� ���(������)
	//void PrintBSPRooms(const BSPNode* InNode);
};


