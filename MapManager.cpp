#include "MapManager.h"
#include <iostream>

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

			switch (InMap.GetCellType(x, y))
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
