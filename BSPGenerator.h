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
	int x, y, Width, Height; //�� ��ǥ, ũ��
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
		//���� ����̰� ���� ��ȿ�ϸ� �� �߽��� ��ȯ
		if (IsLeaf && ContainedRoom.IsValid())
		{
			return ContainedRoom.GetCenter();
		}
		//���� ��尡 �ƴϸ� �ڽ� ��忡�� �� �߽��� ã��
		else if (!IsLeaf)
		{
			if (Left && Left->GetRoomCenter().x != 0)
				return Left->GetRoomCenter();
			if (Right && Right->GetRoomCenter().x !=0)
				return Right->GetRoomCenter();
		}
		//���� ��������� ���� ����.
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

	//Map Ŭ�������� ���͸� �޾� BSP Ʈ�� ���� �� �� ����
	void GenerateMap(Map& InMap, unsigned int MinRoomSize = 10, int MaxDepth = 5);

	//�÷��̾� ���� ��ġ�� ù���� ���� ��� ���� �߽�
	Point GetPlayerSpawn() const;
	vector<Point> GetTokenSpawns(int InCount) const;
	vector<Point> GetEnemiesSpawn(int InCount) const;
	Point GetExitSpawn() const;

private:
	//BSP Ʈ�� ����
	// InNode: ������ ���, MinRoomSize: ���� �ּ� ũ��, InDepth: ���� ����, MaxDepth: �ִ� ����
	void SplitNode(BSPNode* InNode, unsigned int MinRoomSize, int InDepth, int MaxDepth);

	// �� ����
	void CreateRooms(BSPNode* InNode, Map& InMap, unsigned int MinRoomSize);

	//���� ����
	void CreateCorridors(BSPNode* InNodes, Map& InMap);

	//�� ���� �����ϴ� ���� ����
	// InCenter1, InCenter2: ������ �� ���� ���
	void ConnectRooms(const Point& InCenter1, const Point& InCenter2, Map& InMap);

	////���� ��ǥ�� ���� ���(������)
	//void PrintBSPRooms(const BSPNode* InNode);
};


