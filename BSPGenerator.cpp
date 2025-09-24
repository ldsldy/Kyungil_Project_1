#include "BSPGenerator.h"

void BSPGenerator::CreateRoomsInNode(int NodeIndex)
{
	const BSPNode& node = Nodes[NodeIndex];

	int NumRegionsX = node.Width / RegionSize;	//��� �� ���� ���� ����
	int NumRegionsY = node.Height / RegionSize; //��� �� ���� ���� ����
	
	//�� ������ 70% Ȯ���� �� ����
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
	int RegionStartX = Node.x + RegX * RegionSize;	//���� ���� ��ǥ
	int RegionStartY = Node.y + RegY * RegionSize;

	//���� ������ �� ũ�� ���� ����(2*2 ~ 3*3) <= ����Ʈ �ڵ����� �ٲٴ� ����غ���
	int RoomWidth = 2 + FastRandomRange(2);
	int RoomHeight = 2 + FastRandomRange(2);
	
	//���� ������ �� ��ġ ���� ����
	int MaxPosX = RegionStartX + RegionSize - RoomWidth - 1; //-1�� �� ������ ����
	int MaxPosY = RegionStartY + RegionSize - RoomHeight-1;
	int MinPosX = RegionStartX + 1;	//+1�� �� ������ ����
	int MinPosY = RegionStartY + 1;

	//���� ���� ���� �� �� �ִ��� �˻�
	if (MaxPosX >= MinPosX && MaxPosY >= MinPosY)
	{
		//�� ��ġ ���� ����
		int RoomX = MinPosX + FastRandomRange(MaxPosX - MinPosX + 1); //���� ũ�⸸ŭ ���� ��ġ(+1�� �ִ밪 ������ ����)
		int RoomY = MinPosY + FastRandomRange(MaxPosY - MinPosY + 1);
		//�� �Ҵ�
		// RegionStartX/RegionSize, RegionStartY/RegionSize �� �� ��° �������� ��Ÿ��
		AllocateRoom(RoomX, RoomY, RoomWidth, RoomHeight, RegX, RegY);
	}
}

const Room* BSPGenerator::FindRoomInRegion(int RegX, int RegY) const
{
	//���ٽİ� find_if�� �̿��� Ư�� ������ ���ϴ� �� Ž��
	auto it = find_if(Rooms.begin(), Rooms.end(),
		// ĸó ����Ʈ�� RegX, RegY�� �־� ���ٽ� ���ο��� ��� ����
		[RegX, RegY](const Room& room)
		{
			//���� room�� ������ ã���� �ϴ� (RegX, RegY)�� ���� �� true ��ȯ
			int RoomRegX = room.RegionX;
			int RoomRegY = room.RegionY;
			return RoomRegX == RegX && RoomRegY == RegY;
		});
	//ã������ ������ ��ȯ, �� ã������ nullptr ��ȯ
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
	centers.reserve(Rooms.size()); //���� ���� ��ŭ �޸� ����

	for (const auto& room : Rooms)
	{
		centers.push_back(room.GetCenter());
	}
	return centers;
}
