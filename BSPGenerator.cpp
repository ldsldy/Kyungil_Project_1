#include "BSPGenerator.h"
#include "Map.h"
#include <algorithm>
#include <iostream>

//void BSPGenerator::GenerateMap(unsigned int MinRoomSize)
//{
//	if(Root == nullptr)
//		Root = new BSPNode(0, 0, MapLength, MapLength);
//	
//	//BSP 트리 분할
//	SplitNode(Root, MinRoomSize);
//
//	//방 생성
//	CreateRooms(Root, MinRoomSize);
//
//	//복도 생성
//	CreateCorridors(Root);
//
//	GetLeafRoomsVector(LeafRooms);
//	//방의 좌표 디버깅
//	//PrintBSPRooms(Root);
//}
//
//void BSPGenerator::SplitNode(BSPNode* InNode, unsigned int MinRoomSize)
//{
	//int MinRegionLength = MinRoomSize*2+1; //13
	//// 노드가 없으면 종료
	//if (!InNode) return;

	//// 나누어도 방을 만들 수 없는 크기(방이 2개 들어가는 사이즈)인 경우 종료
	//if (InNode->Width <= MinRegionLength && InNode->Height <= MinRegionLength)
	//	return;

	//// 분할 방향 결정
	//bool SplitHorizontally = false;
	//// 가로로 긴 경우 수직 분할
	//if (InNode->Width > InNode->Height && InNode->Width > MinRegionLength)
	//	SplitHorizontally = false;
	//// 세로로 긴 경우 수평 분할
	//else if (InNode->Height > InNode->Width && InNode->Height > MinRegionLength)
	//	SplitHorizontally = true;
	//// 같으면 랜덤
	//else if (InNode->Width > MinRegionLength && InNode->Height > MinRegionLength)
	//	SplitHorizontally = rng() % 2;
	//else
	//	return;

	//// 분할 위치 
	//int SplitPos;
	////수평 분할
	//if (SplitHorizontally)
	//{
	//	SplitPos = MinRoomSize + (rng() % (InNode->Height - MinRoomSize * 2));

	//	InNode->Left = new BSPNode(InNode->x, InNode->y, InNode->Width, SplitPos);
	//	InNode->Right = new BSPNode(InNode->x, InNode->y + SplitPos, InNode->Width, InNode->Height - SplitPos);
	//}
	////수직 분할
	//else
	//{
	//	SplitPos = MinRoomSize + (rng() % (InNode->Width - MinRoomSize * 2));

	//	InNode->Left = new BSPNode(InNode->x, InNode->y, SplitPos, InNode->Height);
	//	InNode->Right = new BSPNode(InNode->x + SplitPos, InNode->y, InNode->Width - SplitPos, InNode->Height);
	//}

	//InNode->IsLeaf = false;

	////재귀적으로 자식 노드 분할
	//SplitNode(InNode->Left, MinRoomSize);
	//SplitNode(InNode->Right, MinRoomSize);
//}
//
//void BSPGenerator::CreateRooms(BSPNode* InNode, unsigned int MinRoomSize)
//{
//	if (!InNode)
//	{
//		//cout << "InNode is null" << endl;
//		return;
//	}
//
//	if (InNode->IsLeaf)
//	{
//		if (InNode->Width >= MinRoomSize+2 && InNode->Height >= MinRoomSize + 2)
//		{
//			//리프 노드에 방 생성 (벽 2개 두께 고려)
//			int RoomWidth = max(MinRoomSize, InNode->Width - 2 - (rng() % 3));
//			int RoomHeight = max(MinRoomSize, InNode->Height - 2 - (rng() % 3));
//
//			//방의 위치는 노드 내부에서 랜덤 (벽 1칸 두께 고려)
//			int RoomX = InNode->x + 1 + (rng() % (InNode->Width - RoomWidth - 1));
//			int RoomY = InNode->y + 1 + (rng() % (InNode->Height - RoomHeight - 1));
//
//			//노드에 방 정보 저장
//			InNode->ContainedRoom = Room(RoomX, RoomY, RoomWidth, RoomHeight);
//
//			//벡터에 방 정보를 저장
//			if (InNode->ContainedRoom.IsValid())
//			{
//				LeafRooms.push_back(InNode->ContainedRoom);
//			}
//			//cout << "Room Created at (" << RoomX << "," << RoomY << ") Size: " << RoomWidth << "x" << RoomHeight << endl;
//
//			//맵에 방 생성
//			for (int y = RoomY; y < RoomY + RoomHeight; y++)
//			{
//				for (int x = RoomX; x < RoomX + RoomWidth; x++)
//				{
//					if (IsValidPosition(x, y))
//					{
//						SetCellType(x, y, CellType::Floor);
//
//					}
//				}
//			}
//		}
//	}
//	else
//	{
//		//재귀적으로 자식 노드에 방 생성
//		CreateRooms(InNode->Left, MinRoomSize);
//		CreateRooms(InNode->Right, MinRoomSize);
//	}
//}
//
//void BSPGenerator::CreateCorridors(BSPNode* InNode)
//{
//	//cout << "복도 생성" << endl;
//	if (!InNode || InNode->IsLeaf) return;
//
//	//자식 노드들에 대해 복도 생성
//	CreateCorridors(InNode->Left);
//	CreateCorridors(InNode->Right);
//
//	//좌우 자식의 방들을 연결
//	if (InNode->Left && InNode->Right)
//	{
//		ConnectRooms(InNode->Left, InNode->Right);
//	}
//}
//
//void BSPGenerator::ConnectRooms(const BSPNode* InRoom1, const BSPNode* InRoom2)
//{
//	
//	Point Center1 = InRoom1->GetRoomCenter();
//	Point Center2 = InRoom2->GetRoomCenter();
//
//	if ((Center1.x <= 0 || Center1.y <= 0) || (Center2.x<=0 ||Center2.y<=0))
//	{
//		/*cout << "One of the rooms is invalid, cannot connect." << endl;*/
//		return;
//	}
//
//	//printf("Corridor connected between (%d, %d) and (%d, %d)\n", Center1.x, Center1.y, Center2.x, Center2.y);
//
//	if (rng() % 2)
//	{
//		//수평-수직 순서의 L자형 복도
//		int StartX = min(Center1.x, Center2.x);
//		int EndX = max(Center1.x, Center2.x);
//		//수평 복도
//		for (int x = StartX; x <= EndX; x++)
//		{
//			if (IsValidPosition(x, Center1.y))
//				SetCellType(x, Center1.y, CellType::Floor);
//		}
//
//		//수직 복도
//		int StartY = min(Center1.y, Center2.y);
//		int EndY = max(Center1.y, Center2.y);
//		for (int y = StartY; y <= EndY; y++)
//		{
//			if (IsValidPosition(Center2.x, y))
//				SetCellType(Center2.x, y, CellType::Floor);
//		}
//	}
//	else
//	{
//		//수직-수평 순서의 L자형 복도
//		int StartY = min(Center1.y, Center2.y);
//		int EndY = max(Center1.y, Center2.y);
//		//수직 복도
//		for (int y = StartY; y <= EndY; y++)
//		{
//			if (IsValidPosition(Center1.x, y))
//				SetCellType(Center1.x, y, CellType::Floor);
//		}
//		//수평 복도
//		int StartX = min(Center1.x, Center2.x);
//		int EndX = max(Center1.x, Center2.x);
//		for (int x = StartX; x <= EndX; x++)
//		{
//			if (IsValidPosition(x, Center2.y))
//				SetCellType(x, Center2.y, CellType::Floor);
//		}
//	}
//}
//
//void BSPGenerator::GetLeafRoomsVector(vector<Room>& InLeafRooms, vector<vector<CellType>> InMapCells)
//{
//	int RoomIndex = 0;
//	PlayerSpawn = InLeafRooms[RoomIndex].GetCenter();
//	//플레이어 시작 위치 설정(첫번째 방의 중앙)
//	SetCellType(PlayerSpawn.x, PlayerSpawn.y, CellType::Start);
//
//	//토큰 위치 설정
//}
//
////생성된 모든 BSPNode들의 Room의 Center값을 출력하는 함수(디버깅용)
//void  BSPGenerator::PrintBSPRooms(const BSPNode* InNode)
//{
//	if (!InNode) return;
//	if (InNode->IsLeaf && InNode->ContainedRoom.IsValid())
//	{
//		Point Center = InNode->ContainedRoom.GetCenter();
//		//std::cout << "Room Center: (" << Center.x << ", " << Center.y << ")\n";
//	}
//	PrintBSPRooms(InNode->Left);
//	PrintBSPRooms(InNode->Right);
//}

void BSPGenerator::GenerateMap(Map& InMap, unsigned int MinRoomSize, int MaxDepth)
{
	
	delete Root;
	LeafRooms.clear();

	InMap.Clear();

	//루트 노드 생성 (맵 테두리는 제외)
	Root = new BSPNode(1, 1, InMap.GetWidth()-2, InMap.GetHeight() - 2);
	
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
	int MinRegionLength = MinRoomSize * 2 + 3;

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
			int RoomX = InNode->x + 1 + (rng() % (InNode->Width - RoomWidth - 1));
			int RoomY = InNode->y + 1 + (rng() % (InNode->Height - RoomHeight - 1));
	
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
	if(!LeafRooms.empty())
		return LeafRooms.back().GetCenter(); //마지막 방의 벽 바깥쪽에 벽 대신 생성
	return Point(0, 0);
}