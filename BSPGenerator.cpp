#include "BSPGenerator.h"

void BSPGenerator::CreateRoomsInNode(int NodeIndex)
{
	const BSPNode& node = Nodes[NodeIndex];

	int NumRegionsX = node.Width / RegionSize;	//노드 내 가로 구역 개수
	int NumRegionsY = node.Height / RegionSize; //노드 내 세로 구역 개수
	
	//각 구역에 70% 확률로 방 생성
	for (int regY = 0; regY < NumRegionsY; regY++)
	{
		for (int regX = 0; regX < NumRegionsX; regX++)
		{
			if (FastRandomRange(100) < 70)
			{
				CreateRoomInRegion(node, regX, regY);
			}
		}
	}

}

void BSPGenerator::CreateRoomInRegion(const BSPNode& Node, int RegX, int RegY)
{
	int RegionStartX = Node.x + RegX * RegionSize;	//구역 시작 좌표
	int RegionStartY = Node.y + RegY * RegionSize;

	//구역 내에서 방 크기 랜덤 결정(2*2 ~ 3*3) <= 소프트 코딩으로 바꾸는 고민해보기
	int RoomWidth = 2 + FastRandomRange(2);
	int RoomHeight = 2 + FastRandomRange(2);
	
	//구역 내에서 방 위치 랜덤 결정
	int MaxPosX = RegionStartX + RegionSize - RoomWidth - 1; //-1은 벽 유지를 위해
	int MaxPosY = RegionStartY + RegionSize - RoomHeight-1;
	int MinPosX = RegionStartX + 1;	//+1은 벽 유지를 위해
	int MinPosY = RegionStartY + 1;

	//방이 구역 내에 들어갈 수 있는지 검사
	if (MaxPosX >= MinPosX && MaxPosY >= MinPosY)
	{
		//방 위치 랜덤 결정
		int RoomX = MinPosX + FastRandomRange(MaxPosX - MinPosX + 1); //방의 크기만큼 랜덤 위치(+1은 최대값 포함을 위해)
		int RoomY = MinPosY + FastRandomRange(MaxPosY - MinPosY + 1);
		//방 할당
		// RegionStartX/RegionSize, RegionStartY/RegionSize 는 몇 번째 구역인지 나타냄
		AllocateRoom(RoomX, RoomY, RoomWidth, RoomHeight, RegX, RegY);
	}
}

const Room* BSPGenerator::FindRoomInRegion(int RegX, int RegY) const
{
	//람다식과 find_if를 이용해 특정 구역에 속하는 방 탐색
	auto it = find_if(Rooms.begin(), Rooms.end(),
		// 캡처 리스트에 RegX, RegY를 넣어 람다식 내부에서 사용 가능
		[RegX, RegY](const Room& room)
		{
			//현재 room의 구역과 찾고자 하는 (RegX, RegY)가 같은 면 true 반환
			int RoomRegX = room.RegionX;
			int RoomRegY = room.RegionY;
			return RoomRegX == RegX && RoomRegY == RegY;
		});
	//찾았으면 포인터 반환, 못 찾았으면 nullptr 반환
	return (it != Rooms.end()) ? &(*it) : nullptr;
}

void BSPGenerator::ConnectRooms(Map& InMap, const Room& InRoom1, const Room& InRoom2)
{
	Point center1 = InRoom1.GetCenter();
	Point center2 = InRoom2.GetCenter();

	CreateCorridors(InMap, center1.x, center1.y, center2.x, center2.y)
}

void BSPGenerator::CreateCorridors(Map& InMap, int InX1, int InY1, int InX2, int InY2)
{
	int CurrentX = InX1;
	int CurrentY = InY1;

	while (CurrentX != InX2)
	{
		if (InMap.IsWall(CurrentX, CurrentY))
		{
			InMap.SetCellType(CurrentX, CurrentY, CellType::Floor);
		}
		CurrentX += (CurrentX > InX2) ? -1 : 1;
	}
	while (CurrentY != InY2)
	{
		if (InMap.IsWall(CurrentX, CurrentY))
		{
			InMap.SetCellType(CurrentX, CurrentY, CellType::Floor);
		}
		CurrentY += (CurrentY > InY2) ? -1 : 1;
	}
	
}

void BSPGenerator::CacheMapInfo(const Map& InMap)
{
	MapSize = InMap.GetMapSize();
	RegionSize = InMap.GetRegionSize();
	NumRegions = InMap.GetMaxNumRegions();
}

float BSPGenerator::GetDistanceBetweenRooms(const Room& room1, const Room& room2) const
{
	Point center1 = room1.GetCenter();
	Point center2 = room2.GetCenter();

	int dx = center2.x - center1.x;
	int dy = center2.y - center1.y;

	return sqrt(dx*dx + dy*dy);
}

vector<Point> BSPGenerator::GetAllRoomCenters() const
{
	vector<Point> centers;
	centers.reserve(Rooms.size()); //방의 갯수 만큼 메모리 예약

	for (const auto& room : Rooms)
	{
		centers.push_back(room.GetCenter());
	}
	return centers;
}
