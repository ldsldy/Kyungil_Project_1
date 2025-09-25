#include "GameManager.h"
#include <iostream>

//참조 매개변수는 복사 방지용, const는 값 보호용, 두개를 함께 쓰는게 좋음
//void PrintMapInTest(Map* InMap);

int main()
{
	cout << "===========맵 테스트==========\n";
	
	//게임 매니저 생성
	GameManager MyGameManger;
	MyGameManger.Run();

	return 0;
}

//void PrintMapInTest(Map* InMap)
//{
//	for (int y = 0; y < InMap->GetMapLength(); y++)
//	{
//		for (int x = 0; x < InMap->GetMapLength(); x++)
//		{
//			switch (InMap->GetCellType(x, y))
//			{
//			case CellType::Wall: 
//				cout.width(2);
//				cout << "■"; break;
//			case CellType::Floor: 
//				cout.width(2);
//				cout << " "; break;
//			case CellType::Token:
//				cout.width(2);
//				cout << "★"; break;
//			case CellType::Exit: 
//				cout.width(2);
//				cout << "E"; break;
//			default:cout << "?"; break;
//			}
//		}
//		cout << endl;
//	}
//}