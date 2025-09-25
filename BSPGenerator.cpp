#include "BSPGenerator.h"
#include "Map.h"
#include <algorithm>
#include <iostream>

void BSPGenerator::GenerateMap(unsigned int MinRoomSize)
{
	if(Root == nullptr)
		Root = new BSPNode(0, 0, MapLength, MapLength);
	
	//BSP Ʈ�� ����
	SplitNode(Root, MinRoomSize);

	//�� ����
	CreateRooms(Root, MinRoomSize);

	//���� ����
	CreateCorridors(Root);

	GetLeafRoomsVector(LeafRooms);
	//���� ��ǥ �����
	//PrintBSPRooms(Root);
}

void BSPGenerator::SplitNode(BSPNode* InNode, unsigned int MinRoomSize)
{
	int MinRegionLength = MinRoomSize*2+1; //13
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

void BSPGenerator::CreateRooms(BSPNode* InNode, unsigned int MinRoomSize)
{
	if (!InNode)
	{
		//cout << "InNode is null" << endl;
		return;
	}

	if (InNode->IsLeaf)
	{
		if (InNode->Width >= MinRoomSize+2 && InNode->Height >= MinRoomSize + 2)
		{
			//���� ��忡 �� ���� (�� 2�� �β� ���)
			int RoomWidth = max(MinRoomSize, InNode->Width - 2 - (rng() % 3));
			int RoomHeight = max(MinRoomSize, InNode->Height - 2 - (rng() % 3));

			//���� ��ġ�� ��� ���ο��� ���� (�� 1ĭ �β� ���)
			int RoomX = InNode->x + 1 + (rng() % (InNode->Width - RoomWidth - 1));
			int RoomY = InNode->y + 1 + (rng() % (InNode->Height - RoomHeight - 1));

			//��忡 �� ���� ����
			InNode->ContainedRoom = Room(RoomX, RoomY, RoomWidth, RoomHeight);

			//���Ϳ� �� ������ ����
			if (InNode->ContainedRoom.IsValid())
			{
				LeafRooms.push_back(InNode->ContainedRoom);
			}
			//cout << "Room Created at (" << RoomX << "," << RoomY << ") Size: " << RoomWidth << "x" << RoomHeight << endl;

			//�ʿ� �� ����
			for (int y = RoomY; y < RoomY + RoomHeight; y++)
			{
				for (int x = RoomX; x < RoomX + RoomWidth; x++)
				{
					if (IsValidPosition(x, y))
					{
						SetCellType(x, y, CellType::Floor);

					}
				}
			}
		}
	}
	else
	{
		//��������� �ڽ� ��忡 �� ����
		CreateRooms(InNode->Left, MinRoomSize);
		CreateRooms(InNode->Right, MinRoomSize);
	}
}

void BSPGenerator::CreateCorridors(BSPNode* InNode)
{
	//cout << "���� ����" << endl;
	if (!InNode || InNode->IsLeaf) return;

	//�ڽ� ���鿡 ���� ���� ����
	CreateCorridors(InNode->Left);
	CreateCorridors(InNode->Right);

	//�¿� �ڽ��� ����� ����
	if (InNode->Left && InNode->Right)
	{
		ConnectRooms(InNode->Left, InNode->Right);
	}
}

void BSPGenerator::ConnectRooms(const BSPNode* InRoom1, const BSPNode* InRoom2)
{
	
	Point Center1 = InRoom1->GetRoomCenter();
	Point Center2 = InRoom2->GetRoomCenter();

	if ((Center1.x <= 0 || Center1.y <= 0) || (Center2.x<=0 ||Center2.y<=0))
	{
		/*cout << "One of the rooms is invalid, cannot connect." << endl;*/
		return;
	}

	//printf("Corridor connected between (%d, %d) and (%d, %d)\n", Center1.x, Center1.y, Center2.x, Center2.y);

	if (rng() % 2)
	{
		//����-���� ������ L���� ����
		int StartX = min(Center1.x, Center2.x);
		int EndX = max(Center1.x, Center2.x);
		//���� ����
		for (int x = StartX; x <= EndX; x++)
		{
			if (IsValidPosition(x, Center1.y))
				SetCellType(x, Center1.y, CellType::Floor);
		}

		//���� ����
		int StartY = min(Center1.y, Center2.y);
		int EndY = max(Center1.y, Center2.y);
		for (int y = StartY; y <= EndY; y++)
		{
			if (IsValidPosition(Center2.x, y))
				SetCellType(Center2.x, y, CellType::Floor);
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
			if (IsValidPosition(Center1.x, y))
				SetCellType(Center1.x, y, CellType::Floor);
		}
		//���� ����
		int StartX = min(Center1.x, Center2.x);
		int EndX = max(Center1.x, Center2.x);
		for (int x = StartX; x <= EndX; x++)
		{
			if (IsValidPosition(x, Center2.y))
				SetCellType(x, Center2.y, CellType::Floor);
		}
	}
}

void BSPGenerator::GetLeafRoomsVector(vector<Room>& InLeafRooms, vector<vector<CellType>> InMapCells)
{
	int RoomIndex = 0;
	PlayerSpawn = InLeafRooms[RoomIndex].GetCenter();
	//�÷��̾� ���� ��ġ ����(ù��° ���� �߾�)
	SetCellType(PlayerSpawn.x, PlayerSpawn.y, CellType::Start);

	//��ū ��ġ ����
}

//������ ��� BSPNode���� Room�� Center���� ����ϴ� �Լ�(������)
void  BSPGenerator::PrintBSPRooms(const BSPNode* InNode)
{
	if (!InNode) return;
	if (InNode->IsLeaf && InNode->ContainedRoom.IsValid())
	{
		Point Center = InNode->ContainedRoom.GetCenter();
		//std::cout << "Room Center: (" << Center.x << ", " << Center.y << ")\n";
	}
	PrintBSPRooms(InNode->Left);
	PrintBSPRooms(InNode->Right);
}