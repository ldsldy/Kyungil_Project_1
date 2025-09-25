#include "Map.h"

Map::Map(int InWidth, int InHeight)
{
	MapData.resize(InHeight, vector<CellType>(InWidth, CellType::Wall));
}

void Map::SetCell(int InX, int InY, CellType Type)
{
	if (IsValidPosition(InX,InY))
	{
		MapData[InY][InX] == Type;
	}
}

CellType Map::GetCell(int InX, int InY) const
{
	if (!IsValidPosition(InX, InY))
		return CellType::Wall;
	return MapData[InY][InX];
}

bool Map::IsWalkable(int InX, int InY) const
{
	if (!IsValidPosition(InX, InY))
		return false;
	
	CellType Cell = GetCell(InX, InY);
	return (Cell==CellType::Exit || Cell == CellType::Player || Cell == CellType::Enemy
		|| Cell == CellType::Floor||Cell==CellType::Token);
}

bool Map::IsValidPosition(int InX, int InY) const
{
	return InX >= 0 && InX < Width && InY >= 0 && InY < Height;
}

bool Map::IsWall(int InX, int InY) const
{
	return GetCell(InX, InY) == CellType::Wall;
}

void Map::Clear()
{
	for (auto& Data : MapData)
	{
		fill(Data.begin(), Data.end(), CellType::Wall);
	}
}

void Map::Print(const Point& PlayerPos) const
{
    //디버깅 콘솔 초기화
    system("cls");

    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            if (PlayerPos.x == x && PlayerPos.y == y)
            {
                cout << "P ";
            }
            else
            {
                switch (GetCell(x, y))
                {
				case CellType::Wall:
					cout.width(2);
					cout << "■"; break;
				case CellType::Floor:
					cout.width(2);
					cout << " "; break;
				case CellType::Token:
					cout.width(2);
					cout << "★"; break;
				case CellType::Exit:
					cout.width(2);
					cout << "E"; break;
				case CellType::Start:
					cout.width(2);
					cout << "S"; break;
				case CellType::Enemy:
					cout.width(2);
					cout << "E"; break;
				default:cout << "?"; break;
                }
            }
        }
        cout << endl;
    }
}