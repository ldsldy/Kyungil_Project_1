#include "BSPGenerator.h"
#include <algorithm>

void BSPGenerator::GenerateMap(Map& InMap, unsigned int MinRoomSize)
{
	InMap.Init();

	//루트 노드 생성
	delete Root;
	Root = new BSPNode(0, 0, InMap.GetMapLength(), InMap.GetMapLength());
	
	//BSP 트리 분할
	SplitNode(Root, MinRoomSize);

	//방 생성
	CreateRooms(Root, InMap, MinRoomSize);

	//복도 생성
	CreateCorridors(Root, InMap);
}

void BSPGenerator::SplitNode(BSPNode* InNode, unsigned int MinRoomSize)
{
	int MinRegionLength = MinRoomSize * 2 + 1;
	// 노드가 없으면 종료
	if (!InNode) return;

	// 나누어도 방을 만들 수 없는 크기(방이 2개 들어가는 사이즈)인 경우 종료
	if (InNode->Width <= MinRegionLength && InNode->Height <= MinRegionLength)
		return;

	// 분할 방향 결정
	bool SplitHorizontally = false;
	// 가로로 긴 경우 수직 분할
	if (InNode->Width > InNode->Height && InNode->Width > MinRegionLength)
		SplitHorizontally = false;
	// 세로로 긴 경우 수평 분할
	else if (InNode->Height > InNode->Width && InNode->Height > MinRegionLength)
		SplitHorizontally = true;
	// 같으면 랜덤
	else if (InNode->Width > MinRegionLength && InNode->Height > MinRegionLength)
		SplitHorizontally = rng() % 2;
	else
		return;

	// 분할 위치 
	int SplitPos;
	//수평 분할
	if (SplitHorizontally)
	{
		SplitPos = MinRoomSize + (rng() % (InNode->Height - MinRoomSize * 2));

		InNode->Left = new BSPNode(InNode->x, InNode->y, InNode->Width, SplitPos);
		InNode->Right = new BSPNode(InNode->x, InNode->y + SplitPos, InNode->Width, InNode->Height - SplitPos);
	}
	//수직 분할
	else
	{
		SplitPos = MinRoomSize + (rng() % (InNode->Width - MinRoomSize * 2));

		InNode->Left = new BSPNode(InNode->x, InNode->y, SplitPos, InNode->Height);
		InNode->Right = new BSPNode(InNode->x + SplitPos, InNode->y, InNode->Width - SplitPos, InNode->Height);
	}

	InNode->IsLeaf = false;

	//재귀적으로 자식 노드 분할
	SplitNode(InNode->Left, MinRoomSize);
	SplitNode(InNode->Right, MinRoomSize);
}

void BSPGenerator::CreateRooms(BSPNode* InNode, Map& InMap, unsigned int MinRoomSize)
{
	if (!InNode) return;

	if (InNode->IsLeaf)
	{
		//리프 노드에 방 생성 (벽 2개 두께 고려)
		int RoomWidth = max(MinRoomSize, InNode->Width - 2 - (rng() % 3));
		int RoomHeight = max(MinRoomSize, InNode->Width - 2 - (rng() % 3));

		//방의 위치는 노드 내부에서 랜덤 (벽 1칸 두께 고려)
		int RoomX = InNode->x + 1 + (rng() % (InNode->Width - RoomWidth - 1));
		int RoomY = InNode->y + 1 + (rng() % (InNode->Height - RoomHeight - 1));

		//맵에 방 생성
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
		InNode->x = RoomX;
		InNode->y = RoomY;
		InNode->Width = RoomWidth;
		InNode->Height = RoomHeight;
	}
	else
	{
		//재귀적으로 자식 노드에 방 생성
		CreateRooms(InNode->Left, InMap, MinRoomSize);
		CreateRooms(InNode->Right, InMap, MinRoomSize);
	}
}

void BSPGenerator::CreateCorridors(BSPNode* InNode, Map& InMap)
{
	if (!InNode || InNode->IsLeaf) return;

	//자식 노드들에 대해 복도 생성
	CreateCorridors(InNode->Left, InMap);
	CreateCorridors(InNode->Right, InMap);

	//좌우 자식의 방들을 연결
	if (InNode->Left && InNode->Right)
	{
		ConnectRooms(InNode->Left, InNode->Right, InMap);
	}
}

void BSPGenerator::ConnectRooms(const BSPNode* InRoom1, const BSPNode* InRoom2, Map& InMap)
{
	Point Center1 = GetRoomCenter(InRoom1);
	Point Center2 = GetRoomCenter(InRoom2);

	if (rng() % 2)
	{
		//수평-수직 순서의 L자형 복도
		int StartX = min(Center1.x, Center2.x);
		int EndX = max(Center1.x, Center2.x);
		for (int x = StartX;)

	}


}

Point BSPGenerator::GetRoomCenter(const BSPNode* InNode) const
{
	if (!InNode) return Point(0, 0);

	if (InNode->IsLeaf)
	{
		return Point(InNode->x + InNode->Width / 2, InNode->y + InNode->Height / 2);
	}
	return Point();
}


