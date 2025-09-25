#include "Map.h"

Map::Map(int InWidth, int InHeight)
{
	MapData.resize(InHeight, vector<CellType>(InWidth, CellType::Wall));
}

void Map::SetCell(int InX, int InY, CellType Type)
{
	if (InX >= 0 && InX < Width && InY >= 0 && InY < Height)
	{
		MapData[InY][InX] == Type;
	}
}

CellType Map::GetCell(int InX, int InY) const
{
	if (InX < 0 || InX >= Width || InY < 0 || InY >= Height)
		return CellType::Wall;
	return MapData[InY][InX];
}

bool Map::IsWalkable(int InX, int InY) const
{
	CellType Cell = GetCell(InX, InY);
	
	return (Cell==CellType::Exit || Cell == CellType::Player || Cell == CellType::Enemy
		|| Cell == CellType::Floor||Cell==CellType::Token);
}

vector<Point> Map::GetRoomCenters() const
{
	return RoomCenters;
}

void Map::AddRoomCenter(const Point& Center)
{
	RoomCenters.push_back(Center);
}

void Map::ClearRoomCenters()
{
	RoomCenters.clear();
}
