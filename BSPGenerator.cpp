#include "BSPGenerator.h"
#include "Map.h"
#include <algorithm>
#include <iostream>

void BSPGenerator::GenerateMap(Map& InMap, unsigned int MinRoomSize, int MaxDepth)
{
	InMap.Clear();
	LeafRooms.clear();

	InMap.Clear();

	//루트 노드 생성 (맵 테두리는 제외)
	Root = new BSPNode(0, 0, InMap.GetWidth(), InMap.GetHeight());
	
	//BSP 트리 분할
	SplitNode(Root, MinRoomSize, 0, MaxDepth);
	
	//방 생성
	CreateRooms(Root, InMap, MinRoomSize);
	
	//복도 생성
	CreateCorridors(Root, InMap);
	
	//방의 좌표 디버깅
	//PrintBSPRooms(Root);
}

void BSPGenerator::SplitNode(BSPNode* InNode, unsigned int MinRoomSize, int InDepth, int MaxDepth)
{
	//노드가 없고 최대 깊이에 도달했으면 종료
	if (!InNode || InDepth >= MaxDepth) 
		return;

	//분할 할 수 있는 최소 크기
	int MinRegionLength = MinRoomSize * 2 + 1;

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
	//수평으로 분할
	if (SplitHorizontally)
	{
		//적어도 한 곳에는 방이 들어갈 수 있도록 분할 위치 결정 
		SplitPos = MinRoomSize + (rng() % (InNode->Height - MinRoomSize * 2));
		InNode->Left = new BSPNode(InNode->x, InNode->y, InNode->Width, SplitPos);
		InNode->Right = new BSPNode(InNode->x, InNode->y + SplitPos, InNode->Width, InNode->Height - SplitPos);
	}
	//수직으로 분할
	else
	{
		SplitPos = MinRoomSize + (rng() % (InNode->Width - MinRoomSize * 2));
		InNode->Left = new BSPNode(InNode->x, InNode->y, SplitPos, InNode->Height);
		InNode->Right = new BSPNode(InNode->x + SplitPos, InNode->y, InNode->Width - SplitPos, InNode->Height);
	}

	//현재 노드는 더 이상 리프 노드가 아님
	InNode->IsLeaf = false;

	//재귀적으로 자식 노드 분할
	SplitNode(InNode->Left, MinRoomSize, InDepth+1, MaxDepth);
	SplitNode(InNode->Right, MinRoomSize, InDepth + 1, MaxDepth);
}

void BSPGenerator::CreateRooms(BSPNode* InNode, Map& InMap, unsigned int MinRoomSize)
{
	if (!InNode)
		return;

	if (InNode->IsLeaf)
	{
		// 영역이 충분히 크면 방 생성
		if (InNode->Width >= MinRoomSize+2 && InNode->Height >= MinRoomSize + 2)
		{
			//벽 2개 두께 고려한 랜덤한 방 크기 (3도 변수로 만들기)
			int RoomWidth = max(MinRoomSize, InNode->Width - 2 - (rng() % 3));
			int RoomHeight = max(MinRoomSize, InNode->Height - 2 - (rng() % 3));
	
			//영역 안의 랜덤한 위치에 방 배치 (시작위치 벽 두께 고려)
			int RoomX = InNode->x +1 + (rng() % (InNode->Width - RoomWidth - 1));
			int RoomY = InNode->y +1 + (rng() % (InNode->Height - RoomHeight - 1));
	
			//노드에 방 정보 저장
			InNode->ContainedRoom = Room(RoomX, RoomY, RoomWidth, RoomHeight);
	
			//벡터에 방 정보를 저장
			if (InNode->ContainedRoom.IsValid()) 
			{
				LeafRooms.push_back(InNode->ContainedRoom);
				InMap.AddRoomCenter(InNode->ContainedRoom.GetCenter());
			}
			//cout << "Room Created at (" << RoomX << "," << RoomY << ") Size: " << RoomWidth << "x" << RoomHeight << endl;
	
			//맵에 방 생성
			for (int y = RoomY; y < RoomY + RoomHeight; y++)
			{
				for (int x = RoomX; x < RoomX + RoomWidth; x++)
				{
					if (InMap.IsValidPosition(x, y))  // 없이도 한번 돌려보기
					{
						InMap.SetCell(x, y, CellType::Floor);
	
					}
				}
			}
		}
	}
	else
	{
		//cout << "방생성 ";
		//재귀적으로 자식 노드에 방 생성
		CreateRooms(InNode->Left, InMap, MinRoomSize);
		CreateRooms(InNode->Right, InMap,MinRoomSize);
	}
}

void BSPGenerator::CreateCorridors(BSPNode* InNode, Map& InMap)
{
	if (!InNode || InNode->IsLeaf) 
		return;

	//자식 노드들에 대해 복도 생성
	CreateCorridors(InNode->Left, InMap);
	CreateCorridors(InNode->Right, InMap);

	//좌우 자식의 방들을 연결
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
		//수평-수직 순서로 복도 생성
		int StartX = min(InCenter1.x, InCenter2.x);
		int EndX = max(InCenter1.x, InCenter2.x);
		//수평 복도
		for (int x = StartX; x <= EndX; x++)
		{
			if (IsValidPosition(x, InCenter1.y)) // 없이도 한번 돌려보기
				InMap.SetCell(x, InCenter1.y, CellType::Floor);
		}
	
		//수직 복도
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
		//수직-수평 순서로 복도 생성
 		int StartY = min(InCenter1.y, InCenter2.y);
		int EndY = max(InCenter1.y, InCenter2.y);
		//수직 복도
		for (int y = StartY; y <= EndY; y++)
		{
			if (IsValidPosition(InCenter1.x, y))
				InMap.SetCell(InCenter1.x, y, CellType::Floor);
		}
		//수평 복도
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
			TokenSpawns.push_back(LeafRooms[i].GetCenter()); //센터가 아닌 랜덤 위치로 바꾸기
		else
			break;
	}
	if(TokenSpawns.size() < InCount)
	{
		cout << "토큰을 전부 생성하지 못했습니다." << endl;
		//같은 방에 여러 토큰 또 추가
	}
	return TokenSpawns;
}

Point BSPGenerator::GetEnemySpawn() const
{
	if (LeafRooms.size() > 2)
		return LeafRooms[LeafRooms.size() / 2].GetCenter(); //리프룸 노드 선택을 랜덤하게 바꾸기
	return Point();
}

Point BSPGenerator::GetExitSpawn() const
{
	if (!LeafRooms.empty()) 
	{
		cout << "출구가 생성되었습니다.\n";
		cout << "LeafRooms.bakc(): " << LeafRooms.back().x << ", " << LeafRooms.back().y << endl;
		return LeafRooms.back().GetCenter(); //마지막 방의 벽 바깥쪽에 벽 대신 생성
	}
	return Point(-1, -1);
}