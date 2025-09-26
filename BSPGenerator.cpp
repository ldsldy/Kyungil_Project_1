#include "BSPGenerator.h"
#include "Map.h"
#include <algorithm>
#include <iostream>

void BSPGenerator::GenerateMap(Map& InMap, unsigned int MinRoomSize, int MaxDepth)
{
	InMap.Clear();
	LeafRooms.clear();

	InMap.Clear();

	//��Ʈ ��� ���� (�� �׵θ��� ����)
	Root = new BSPNode(0, 0, InMap.GetWidth(), InMap.GetHeight());
	
	//BSP Ʈ�� ����
	SplitNode(Root, MinRoomSize, 0, MaxDepth);
	
	//�� ����
	CreateRooms(Root, InMap, MinRoomSize);
	
	//���� ����
	CreateCorridors(Root, InMap);
	
	//���� ��ǥ �����
	//PrintBSPRooms(Root);
}

void BSPGenerator::SplitNode(BSPNode* InNode, unsigned int MinRoomSize, int InDepth, int MaxDepth)
{
	//��尡 ���� �ִ� ���̿� ���������� ����
	if (!InNode || InDepth >= MaxDepth) 
		return;

	//���� �� �� �ִ� �ּ� ũ��
	int MinRegionLength = MinRoomSize * 2 + 1;

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
	//�������� ����
	if (SplitHorizontally)
	{
		//��� �� ������ ���� �� �� �ֵ��� ���� ��ġ ���� 
		SplitPos = MinRoomSize + (rng() % (InNode->Height - MinRoomSize * 2));
		InNode->Left = new BSPNode(InNode->x, InNode->y, InNode->Width, SplitPos);
		InNode->Right = new BSPNode(InNode->x, InNode->y + SplitPos, InNode->Width, InNode->Height - SplitPos);
	}
	//�������� ����
	else
	{
		SplitPos = MinRoomSize + (rng() % (InNode->Width - MinRoomSize * 2));
		InNode->Left = new BSPNode(InNode->x, InNode->y, SplitPos, InNode->Height);
		InNode->Right = new BSPNode(InNode->x + SplitPos, InNode->y, InNode->Width - SplitPos, InNode->Height);
	}

	//���� ���� �� �̻� ���� ��尡 �ƴ�
	InNode->IsLeaf = false;

	//��������� �ڽ� ��� ����
	SplitNode(InNode->Left, MinRoomSize, InDepth+1, MaxDepth);
	SplitNode(InNode->Right, MinRoomSize, InDepth + 1, MaxDepth);
}

void BSPGenerator::CreateRooms(BSPNode* InNode, Map& InMap, unsigned int MinRoomSize)
{
	if (!InNode)
		return;

	if (InNode->IsLeaf)
	{
		// ������ ����� ũ�� �� ����
		if (InNode->Width >= MinRoomSize+2 && InNode->Height >= MinRoomSize + 2)
		{
			//�� 2�� �β� ����� ������ �� ũ�� (3�� ������ �����)
			int RoomWidth = max(MinRoomSize, InNode->Width - 2 - (rng() % 3));
			int RoomHeight = max(MinRoomSize, InNode->Height - 2 - (rng() % 3));
	
			//���� ���� ������ ��ġ�� �� ��ġ (������ġ �� �β� ���)
			int RoomX = InNode->x +1 + (rng() % (InNode->Width - RoomWidth - 1));
			int RoomY = InNode->y +1 + (rng() % (InNode->Height - RoomHeight - 1));
	
			//��忡 �� ���� ����
			InNode->ContainedRoom = Room(RoomX, RoomY, RoomWidth, RoomHeight);
	
			//���Ϳ� �� ������ ����
			if (InNode->ContainedRoom.IsValid()) 
			{
				LeafRooms.push_back(InNode->ContainedRoom);
				InMap.AddRoomCenter(InNode->ContainedRoom.GetCenter());
			}
			//cout << "Room Created at (" << RoomX << "," << RoomY << ") Size: " << RoomWidth << "x" << RoomHeight << endl;
	
			//�ʿ� �� ����
			for (int y = RoomY; y < RoomY + RoomHeight; y++)
			{
				for (int x = RoomX; x < RoomX + RoomWidth; x++)
				{
					if (InMap.IsValidPosition(x, y))  // ���̵� �ѹ� ��������
					{
						InMap.SetCell(x, y, CellType::Floor);
	
					}
				}
			}
		}
	}
	else
	{
		//cout << "����� ";
		//��������� �ڽ� ��忡 �� ����
		CreateRooms(InNode->Left, InMap, MinRoomSize);
		CreateRooms(InNode->Right, InMap,MinRoomSize);
	}
}

void BSPGenerator::CreateCorridors(BSPNode* InNode, Map& InMap)
{
	if (!InNode || InNode->IsLeaf) 
		return;

	//�ڽ� ���鿡 ���� ���� ����
	CreateCorridors(InNode->Left, InMap);
	CreateCorridors(InNode->Right, InMap);

	//�¿� �ڽ��� ����� ����
	if (InNode->Left && InNode->Right)
	{
		Point CenterLeft = InNode->Left->GetRoomCenter();
		Point CenterRight = InNode -> Right->GetRoomCenter();

		if (CenterLeft.x > 0 && CenterLeft.y > 0 && CenterRight.x > 0 && CenterRight.y > 0)
		{
			ConnectRooms(CenterLeft, CenterRight, InMap);
		}
	}
}

void BSPGenerator::ConnectRooms(const Point& InCenter1, const Point& InCenter2, Map& InMap)
{
	if (rng() % 2)
	{
		//����-���� ������ ���� ����
		int StartX = min(InCenter1.x, InCenter2.x);
		int EndX = max(InCenter1.x, InCenter2.x);
		//���� ����
		for (int x = StartX; x <= EndX; x++)
		{
			if (IsValidPosition(x, InCenter1.y)) // ���̵� �ѹ� ��������
				InMap.SetCell(x, InCenter1.y, CellType::Floor);
		}
	
		//���� ����
		int StartY = min(InCenter1.y, InCenter2.y);
		int EndY = max(InCenter1.y, InCenter2.y);
		for (int y = StartY; y <= EndY; y++)
		{
			if (IsValidPosition(InCenter2.x, y))
				InMap.SetCell(InCenter2.x, y, CellType::Floor);
		}
	}
	else
	{
		//����-���� ������ ���� ����
 		int StartY = min(InCenter1.y, InCenter2.y);
		int EndY = max(InCenter1.y, InCenter2.y);
		//���� ����
		for (int y = StartY; y <= EndY; y++)
		{
			if (IsValidPosition(InCenter1.x, y))
				InMap.SetCell(InCenter1.x, y, CellType::Floor);
		}
		//���� ����
		int StartX = min(InCenter1.x, InCenter2.x);
		int EndX = max(InCenter1.x, InCenter2.x);
		for (int x = StartX; x <= EndX; x++)
		{
			if (IsValidPosition(x, InCenter2.y))
				InMap.SetCell(x, InCenter2.y, CellType::Floor);
		}
	}
}

Point BSPGenerator::GetPlayerSpawn() const
{
	if (!LeafRooms.empty())
	{
		return LeafRooms[0].GetCenter();
	}
	return Point(0,0);
}

vector<Point> BSPGenerator::GetTokenSpawns(int InCount) const
{
	vector<Point> TokenSpawns;
	for (int i = 1; TokenSpawns.size() < InCount; i++)
	{
		if (LeafRooms.size() > i)
			TokenSpawns.push_back(LeafRooms[i].GetCenter()); //���Ͱ� �ƴ� ���� ��ġ�� �ٲٱ�
		else
			break;
	}
	if(TokenSpawns.size() < InCount)
	{
		cout << "��ū�� ���� �������� ���߽��ϴ�." << endl;
		//���� �濡 ���� ��ū �� �߰�
	}
	return TokenSpawns;
}

Point BSPGenerator::GetEnemySpawn() const
{
	if (LeafRooms.size() > 2)
		return LeafRooms[LeafRooms.size() / 2].GetCenter(); //������ ��� ������ �����ϰ� �ٲٱ�
	return Point();
}

Point BSPGenerator::GetExitSpawn() const
{
	if (!LeafRooms.empty()) 
	{
		cout << "�ⱸ�� �����Ǿ����ϴ�.\n";
		cout << "LeafRooms.bakc(): " << LeafRooms.back().x << ", " << LeafRooms.back().y << endl;
		return LeafRooms.back().GetCenter(); //������ ���� �� �ٱ��ʿ� �� ��� ����
	}
	return Point(-1, -1);
}