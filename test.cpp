#include "MapManager.h"
#include "BSPGenerator.h"
#include "Map.h"
#include "GameManager.h"
#include <iostream>

void PrintMapInTest(Map* InMap);

int main()
{

	cout << "====맵 생성기 테스트==========\n";
	////맵 매니저 생성
	//MapManager MyMapManager;
	////맵 출력
	//MyMapManager.PrintMap();

	//게임 매니저 생성
	GameManager* MyGameManger;
	MyGameManger = new GameManager;
	MyGameManger->Run();


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
			default:cout << "?"; break;
			}
		}
		cout << endl;
	}
}