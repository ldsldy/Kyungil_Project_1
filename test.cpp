#include "GameManager.h"
#include "Map.h"
#include "BSPGenerator.h"
#include <iostream>

//참조 매개변수는 복사 방지용, const는 값 보호용, 두개를 함께 쓰는게 좋음
//void PrintMapInTest(Map* InMap);

int main()
{
	cout << "===========맵 테스트==========\n";
	
	//게임 매니저 생성
	GameManager MyGameManger;
	MyGameManger.Run();

	////맵 생성
	/*Map MyMap(64, 64);
	BSPGenerator GameMapGenerator;

	GameMapGenerator.GenerateMap(MyMap, 6, 16);

	MyMap.Print(Point(2, 2));*/

	return 0;
}
