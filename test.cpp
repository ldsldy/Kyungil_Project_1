#include "GameManager.h"
#include "Map.h"
#include "BSPGenerator.h"
#include <iostream>

//참조 매개변수는 복사 방지용, const는 값 보호용, 두개를 함께 쓰는게 좋음
//void PrintMapInTest(Map* InMap);

int main()
{	
	//게임 매니저 생성
	GameManager MyGameManger;
	MyGameManger.Run();


	return 0;
}
