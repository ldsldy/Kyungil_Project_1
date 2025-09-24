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
			case CellType::Wall: cout << "��"; break;
			case CellType::Floor: cout << " "; break;
			case CellType::Item: cout << "��"; break;
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
	// 5ĭ���� ���� ���м� �߰�
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
		//5ĭ���� ���� ���м� �߰�
		for (int x = 0; x < MapLength; x++)
		{
			if (x % RegionSize == 0 && x > 0)
			{
				cout << "|";
			}

			switch (ManagerMap->GetCellType(x, y))
			{
			case CellType::Wall: cout << "��"; break;
			case CellType::Floor: cout << "��"; break;
			case CellType::Item: cout << "��"; break;
			case CellType::Exit: cout << "��"; break;
			}

		}
		cout << endl;
	}
	cout << endl;
}

void MapManager::PrintRegionMap() const
{
	cout << "Map�� �Ѻκ� (" << MapLength << "x" << MapLength << "):\n";
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

	std::cout << "\n=== �� ��� ===\n";
	std::cout << "�� �� ��: " << MapLength * MapLength << std::endl;
	std::cout << "��: " << WallCount << "��" << std::endl;
	std::cout << "�� ����: " << FloorCount << "��" << std::endl;
	std::cout << "������: " << ItemCount << "��" << std::endl;
	std::cout << "�ⱸ: " << ExitCount << "��" << std::endl;
	std::cout << "===============\n";
}

void MapManager::DataCaching()
{
	MapLength = ManagerMap->GetMapLength();
	RegionSize = ManagerMap->GetRegionSize();
	MapManagerToken = 0;
}
