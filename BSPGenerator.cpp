#include "BSPGenerator.h"
#include <algorithm>

void BSPGenerator::GenerateMap(Map& InMap, unsigned int MinRoomSize)
{
	InMap.Init();

	//루트 노드 안전한 메모리 관리
	if (Root != nullptr) {
		delete Root;
		Root = nullptr;
	}
	Root = new BSPNode(0, 0, InMap.GetMapLength(), InMap.GetMapLength());
	
	//BSP Ʈ�� ����
	SplitNode(Root, MinRoomSize);

	//�� ����
	CreateRooms(Root, InMap, MinRoomSize);

	//���� ����
	CreateCorridors(Root, InMap);
}

void BSPGenerator::SplitNode(BSPNode* InNode, unsigned int MinRoomSize)
{
	int MinRegionLength = MinRoomSize * 2 + 1;
	// ��尡 ������ ����
	if (!InNode) return;

	// ����� ���� ���� �� ���� ũ��(���� 2�� ���� ������)�� ��� ����
	if (InNode->Width <= MinRegionLength && InNode->Height <= MinRegionLength)
		return;

	// ���� ���� ����
	bool SplitHorizontally = false;
	// ���η� �� ��� ���� ����
	if (InNode->Width > InNode->Height && InNode->Width > MinRegionLength)
		SplitHorizontally = false;
	// ���η� �� ��� ���� ����
	else if (InNode->Height > InNode->Width && InNode->Height > MinRegionLength)
		SplitHorizontally = true;
	// ������ ����
	else if (InNode->Width > MinRegionLength && InNode->Height > MinRegionLength)
		SplitHorizontally = rng() % 2;
	else
		return;

	// ���� ��ġ 
	int SplitPos;
	//���� ����
	if (SplitHorizontally)
	{
		SplitPos = MinRoomSize + (rng() % (InNode->Height - MinRoomSize * 2));

		InNode->Left = new BSPNode(InNode->x, InNode->y, InNode->Width, SplitPos);
		InNode->Right = new BSPNode(InNode->x, InNode->y + SplitPos, InNode->Width, InNode->Height - SplitPos);
	}
	//���� ����
	else
	{
		SplitPos = MinRoomSize + (rng() % (InNode->Width - MinRoomSize * 2));

		InNode->Left = new BSPNode(InNode->x, InNode->y, SplitPos, InNode->Height);
		InNode->Right = new BSPNode(InNode->x + SplitPos, InNode->y, InNode->Width - SplitPos, InNode->Height);
	}

	InNode->IsLeaf = false;

	//��������� �ڽ� ��� ����
	SplitNode(InNode->Left, MinRoomSize);
	SplitNode(InNode->Right, MinRoomSize);
}

void BSPGenerator::CreateRooms(BSPNode* InNode, Map& InMap, unsigned int MinRoomSize)
{
	if (!InNode) return;

	if (InNode->IsLeaf)
	{
		//���� ��忡 �� ���� (�� 2�� �β� ����)
		int RoomWidth = max((int)MinRoomSize, InNode->Width - 2 - (int)(rng() % 3));
		int RoomHeight = max((int)MinRoomSize, InNode->Height - 2 - (int)(rng() % 3));

		//���� ��ġ�� ��� ���ο��� ���� (�� 1ĭ �β� ����)
		int RoomX = InNode->x + 1 + (rng() % (InNode->Width - RoomWidth - 1));
		int RoomY = InNode->y + 1 + (rng() % (InNode->Height - RoomHeight - 1));
		
		//��忡 �� ���� ����
		InNode->ContainedRoom = Room(RoomX, RoomY, RoomWidth, RoomHeight);

		//�ʿ� �� ����
		for (int y = RoomY; y < RoomY + RoomHeight; y++)
		{
			for (int x = RoomX; x < RoomX + RoomWidth; x++)
			{
				if (InMap.IsValidPosition(x, y))
				{
					InMap.SetCellType(x, y, CellType::Floor);
				}
			}
		}
	}
	else
	{
		//��������� �ڽ� ��忡 �� ����
		CreateRooms(InNode->Left, InMap, MinRoomSize);
		CreateRooms(InNode->Right, InMap, MinRoomSize);
	}
}

void BSPGenerator::CreateCorridors(BSPNode* InNode, Map& InMap)
{
	if (!InNode || InNode->IsLeaf) return;

	//�ڽ� ���鿡 ���� ���� ����
	CreateCorridors(InNode->Left, InMap);
	CreateCorridors(InNode->Right, InMap);

	//�¿� �ڽ��� ����� ����
	if (InNode->Left && InNode->Right)
	{
		ConnectRooms(InNode->Left, InNode->Right, InMap);
	}
}

void BSPGenerator::ConnectRooms(const BSPNode* InRoom1, const BSPNode* InRoom2, Map& InMap)
{
	Point Center1 = InRoom1->GetRoomCenter();
	Point Center2 = InRoom2->GetRoomCenter();

	if (rng() % 2)
	{
		//����-���� ������ L���� ����
		int StartX = min(Center1.x, Center2.x);
		int EndX = max(Center1.x, Center2.x);
		//���� ����
		for (int x = StartX; x <= EndX; x++)
		{
			if (InMap.IsValidPosition(x, Center1.y))
				InMap.SetCellType(x, Center1.y, CellType::Floor);
		}

		//���� ����
		int StartY = min(Center1.y, Center2.y);
		int EndY = max(Center1.y, Center2.y);
		for (int y = StartY; y <= EndY; y++)
		{
			if (InMap.IsValidPosition(Center2.x, y))
				InMap.SetCellType(Center2.x, y, CellType::Floor);
		}
	}
	else
	{
		//����-���� ������ L���� ����
		int StartY = min(Center1.y, Center2.y);
		int EndY = max(Center1.y, Center2.y);
		//���� ����
		for (int y = StartY; y <= EndY; y++)
		{
			if (InMap.IsValidPosition(Center1.x, y))
				InMap.SetCellType(Center1.x, y, CellType::Floor);
		}
		//���� ����
		int StartX = min(Center1.x, Center2.x);
		int EndX = max(Center1.x, Center2.x);
		for (int x = StartX; x <= EndX; x++)
		{
			if (InMap.IsValidPosition(x, Center2.y))
				InMap.SetCellType(x, Center2.y, CellType::Floor);
		}
	}
}