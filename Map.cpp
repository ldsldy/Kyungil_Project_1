#include "Map.h"
#include <iostream>

void Map::PrintTestMap() const
{
	cout << "Map (" << Width << "x" << Height << "):\n";
	// 5ĭ���� ���� ���м� �߰�
	for (int y = 0; y < Height; y++)
	{
		if (y % 5 == 0 && y > 0)
		{
			for (int x = 0; x < Width; x++)
			{
				cout << (x % 5 == 0 && x > 0 ? "+" : "-");
			}
			cout << "\n";
		}
		//5ĭ���� ���� ���м� �߰�
		for (int x = 0; x < Width; x++)
		{
			if (x % 5 == 0 && x > 0)
			{
				cout << "|";
			}
			
			switch (MapData[y][x])
			{
			case CellType::Wall: cout << "��"; break;
			case CellType::Empty: cout << "��"; break;
			case CellType::Item: cout << "��"; break;
			case CellType::Exit: cout << "��"; break;
			}

		}
		cout << endl;
	}
	cout << endl;
}

void Map::PrintRegionMap() const
{
	cout << "Map�� �Ѻκ� (" << Width << "x" << Height << "):\n";
	for (int RegY = 0; RegY < 5; RegY++)
	{
		for (int RegX = 0; RegX < 5; RegX++)
		{
			cout << "[" << RegY * 5 + RegX + 1 << "] ";
		}
		cout << "\n";
	}
	cout << endl;
}
