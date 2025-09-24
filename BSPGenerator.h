#pragma once
#include <vector>
#include <random>
#include "Map.h"
#include "Point.h"

using namespace std;

Map InMap; //���� ����

//BSP��� - �ε��� ��� ���� ���� 
struct BSPNode
{
	int x, y, Width, Height; //�� ��ǥ, ũ��
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

	//Map Ŭ�������� ���͸� �޾� BSP Ʈ�� ���� �� �� ����
	void GenerateMap(Map& InMap, unsigned int MinRoomSize = 0);

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



