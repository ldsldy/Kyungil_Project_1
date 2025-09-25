#include "MapManager.h"
#include "BSPGenerator.h"
#include "Map.h"
#include <iostream>

void PrintMapInTest(Map* InMap);

int main()
{

	cout << "====¸Ê »ý¼º±â Å×½ºÆ®==========\n";
	//¸Ê ¸Å´ÏÀú »ý¼º
	//MapManager MyMapManager;
	//¸Ê Ãâ·Â
	//MyMapManager.PrintMap();
	Map  MyMap;
	BSPGenerator* MyBSPGen;
	MyBSPGen = new BSPGenerator();
	MyBSPGen->GenerateMap(MyMap, 10);
	PrintMapInTest(&MyMap);

	return 0;
}

void PrintMapInTest(Map* InMap)
{
	for (int y = 0; y < InMap->GetMapLength(); y++)
	{
		for (int x = 0; x < InMap->GetMapLength(); x++)
		{
			switch (InMap->GetCellType(x, y))
			{
			case CellType::Wall: 
				cout.width(2);
				cout << "¡á"; break;
			case CellType::Floor: 
				cout.width(2);
				cout << " "; break;
			case CellType::Item: 
				cout.width(2);
				cout << "¡Ú"; break;
			case CellType::Exit: 
				cout.width(2);
				cout << "E"; break;
			default:cout << "?"; break;
			}
		}
		cout << endl;
	}
}