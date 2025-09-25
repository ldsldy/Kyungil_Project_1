#include "MapManager.h"
#include "GameManager.h"
#include <iostream>

void MapManager::Init()
{
	GenerateMap(MapCells, 10);
}

void MapManager::PrintMap() const
{
	cout << "InPrint" << endl;
	for (int y = 0; y < CurrentMapManager->GetMapLengthFromMap(); y++)
	{
		for (int x = 0; x < CurrentMapManager->GetMapLengthFromMap(); x++)
		{
			if (GetCurrentPlayerPos().x == x
				&& GetCurrentPlayerPos().y == y)
			{
				cout.width(2);
				cout << "P" << endl;
			}
			else
			{
				switch (ManagerMap->GetCellType(x, y))
				{
				case CellType::Wall:
					cout.width(2);
					cout << "¡á"; break;
				case CellType::Floor:
					cout.width(2);
					cout << " "; break;
				case CellType::Token:
					cout.width(2);
					cout << "¡Ú"; break;
				case CellType::Exit:
					cout.width(2);
					cout << "E"; break;
				case CellType::Start:
					cout.width(2);
					cout << "S"; break;
				default:cout << "?"; break;
				}
			}
		}
		cout << endl;
	}
}

void MapManager::PrintMapInfo() const
{
	int WallCount = 0, FloorCount = 0, TokenCount = 0, ExitCount = 0;

	for (int y = 0; y < MapLength; y++)
	{
		for (int x = 0; x < MapLength; x++)
		{
			switch (ManagerMap->GetCellType(x, y))
			{
			case CellType::Wall: WallCount++; break;
			case CellType::Floor: FloorCount++; break;
			case CellType::Token: TokenCount++; break;
			case CellType::Exit: ExitCount++; break;
			}
		}
	}

	std::cout << "\n=== ¸Ê Åë°è ===\n";
	std::cout << "ÃÑ ¼¿ ¼ö: " << MapLength * MapLength << std::endl;
	std::cout << "º®: " << WallCount << "°³" << std::endl;
	std::cout << "ºó °ø°£: " << FloorCount << "°³" << std::endl;
	std::cout << "¾ÆÀÌÅÛ: " << TokenCount << "°³" << std::endl;
	std::cout << "Ãâ±¸: " << ExitCount << "°³" << std::endl;
	std::cout << "===============\n";
}