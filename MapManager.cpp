#include "MapManager.h"
#include <iostream>

void MapManager::GenerateBSPMap(unsigned int MinRoomSize)
{
	ManagerMap = new Map();
	BSPGen = new BSPGenerator();
	BSPGen->GenerateMap(*ManagerMap, MinRoomSize);
}

void MapManager::PrintMap() const
{
	for(int y=0; y<MapLength; y++)
	{
		for(int x=0; x<MapLength; x++)
		{
			switch (ManagerMap->GetCellType(x, y))
			{
			case CellType::Wall: cout << "■"; break;
			case CellType::Floor: cout << " "; break;
			case CellType::Item: cout << "★"; break;
			case CellType::Exit: cout << "E"; break;
			default:cout << "?"; break;
			}
		}
		cout << endl;
	}
}

void MapManager::PrintTestMap() const
{
	cout << "Map (" << MapLength << "x" << MapLength << "):\n";
	// 5칸마다 가로 구분선 추가
	for (int y = 0; y < MapLength; y++)
	{
		if (y % RegionSize == 0 && y > 0)
		{
			for (int x = 0; x < MapLength; x++)
			{
				cout << (x % RegionSize == 0 && x > 0 ? "+" : "-");
			}
			cout << "\n";
		}
		//5칸마다 세로 구분선 추가
		for (int x = 0; x < MapLength; x++)
		{
			if (x % RegionSize == 0 && x > 0)
			{
				cout << "|";
			}

			switch (ManagerMap->GetCellType(x, y))
			{
			case CellType::Wall: cout << "■"; break;
			case CellType::Floor: cout << "□"; break;
			case CellType::Item: cout << "★"; break;
			case CellType::Exit: cout << "◇"; break;
			}

		}
		cout << endl;
	}
	cout << endl;
}

void MapManager::PrintRegionMap() const
{
	cout << "Map의 한부분 (" << MapLength << "x" << MapLength << "):\n";
	for (int RegY = 0; RegY < RegionSize; RegY++)
	{
		for (int RegX = 0; RegX < RegionSize; RegX++)
		{
			cout << "[" << RegY * RegionSize + RegX + 1 << "] ";
		}
		cout << "\n";
	}
	cout << endl;
}

void MapManager::PrintMapInfo() const
{
	int WallCount = 0, FloorCount = 0, ItemCount = 0, ExitCount = 0;

	for (int y = 0; y < MapLength; y++)
	{
		for (int x = 0; x < MapLength; x++)
		{
			switch (ManagerMap->GetCellType(x, y))
			{
			case CellType::Wall: WallCount++; break;
			case CellType::Floor: FloorCount++; break;
			case CellType::Item: ItemCount++; break;
			case CellType::Exit: ExitCount++; break;
			}
		}
	}

	std::cout << "\n=== 맵 통계 ===\n";
	std::cout << "총 셀 수: " << MapLength * MapLength << std::endl;
	std::cout << "벽: " << WallCount << "개" << std::endl;
	std::cout << "빈 공간: " << FloorCount << "개" << std::endl;
	std::cout << "아이템: " << ItemCount << "개" << std::endl;
	std::cout << "출구: " << ExitCount << "개" << std::endl;
	std::cout << "===============\n";
}

void MapManager::DataCaching()
{
	MapLength = ManagerMap->GetMapLength();
	RegionSize = ManagerMap->GetRegionSize();
	MapManagerToken = 0;
}
