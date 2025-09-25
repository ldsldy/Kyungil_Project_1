#include "Map.h"
//#include <Windows.h>d
Map::Map(int InWidth, int InHeight)
{
	Width = InWidth;
	Height = InHeight;
	MapData.resize(InHeight, vector<CellType>(InWidth, CellType::Wall));
	cout << "Map Created. Width: " << InWidth << ", Height: " << InHeight << endl;
}

void Map::SetCell(int InX, int InY, CellType Type)
{
	if (IsValidPosition(InX,InY))
	{
		MapData[InY][InX] = Type;
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
	system("cls");
	cout << "Height: " << Height << ", Width: " << Width << endl;
    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            if (PlayerPos.x == x && PlayerPos.y == y)
            {
				//cout.width(2);
                cout << "P";
            }
            else
            {
                switch (GetCell(x, y))
                {
				case CellType::Wall:
					//cout.width(2);
					cout << "W";
					//cout << "■"; 
					break;
				case CellType::Floor:
					//cout.width(2);
					cout << " "; 
					break;
				case CellType::Token:
					//cout.width(2);
					cout << "T";
					//cout << "★"; 
					break;
				case CellType::Exit:
					//cout.width(2);
					cout << "E"; 
					break;
				case CellType::Start:
					//cout.width(2);
					cout << "S"; 
					break;
				case CellType::Enemy:
					//cout.width(2);
					cout << "X"; 
					break;
				default:cout << "?"; break;
                }
            }
        }
        cout << endl;
    }
	
}

void Map::PrintDarkMode(const Point& PlayerPos) const
{
	//부분 출력
	system("cls");
	int ShowStartX = PlayerPos.x - 8;
	int ShowStartY = PlayerPos.y - 8;
	int ShowEndX = PlayerPos.x + 8;
	int ShowEndY = PlayerPos.y + 8;
	cout << "Height: 16" << ", Width: 16" << endl;
	for (int y = ShowStartY; y < ShowEndY; y++)
	{
		for (int x = ShowStartX; x < ShowEndX; x++)
		{
			if (x < 0 || x >= Width || y < 0 || y >= Height)
			{
				std::cout << " ";
			}
			else if (PlayerPos.x == x && PlayerPos.y == y)
			{
				//cout.width(2);
				cout << "P";
			}
			else
			{
				switch (GetCell(x, y))
				{
				case CellType::Wall:
					//cout.width(2);
					cout << "W";
					//cout << "■"; 
					break;
				case CellType::Floor:
					//cout.width(2);
					cout << " ";
					break;
				case CellType::Token:
					//cout.width(2);
					cout << "T";
					//cout << "★"; 
					break;
				case CellType::Exit:
					//cout.width(2);
					cout << "E";
					break;
				case CellType::Start:
					//cout.width(2);
					cout << "S";
					break;
				case CellType::Enemy:
					//cout.width(2);
					cout << "X";
					break;
				default:cout << "?"; break;
				}
			}
		}
		cout << endl;
	}
}
