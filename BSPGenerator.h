#pragma once
#include <vector>
#include <random>
#include "Map.h"
#include "Point.h"

using namespace std;

Map InMap; //���� ����

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

	~BSPNode()
	{
		delete Left;
		delete Right;
	}

	inline Point GetRoomCenter() const 
	{
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
		return Point(0, 0); // Default return value
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

	//Map Ŭ�������� ���͸� �޾� BSP Ʈ�� ���� �� �� ����
	void GenerateMap(Map& InMap, unsigned int MinRoomSize = 6);

private:
	BSPNode* Root;
	mt19937 rng;

	//BSP Ʈ�� ����
	void SplitNode(BSPNode* InNode, unsigned int MinRoomSize);

	// �� ����
	void CreateRooms(BSPNode* InNode, Map& InMap, unsigned int MinRoomSize);

	//���� ����
	void CreateCorridors(BSPNode* InNode, Map& InMap);

	//�� ���� �����ϴ� ���� ����
	void ConnectRooms(const BSPNode* InRoom1, const BSPNode* InRoom2, Map& InMap);

	//������ �߽��� ã��
	Point GetRoomCenter(const BSPNode* InNode) const;
};



