#include "MapManager.h"
#include <iostream>
//단일 책임
//게임 매니저를 통하자

//플레이어, 적, 맵이 게임 매니저에게 무엇을 했는지 알리면 게임 매니저가 처리해서
//다른 클래스로 뿌린다.
int main()
{
	cout << "====맵 생성기 테스트==========\n";
	//맵 매니저 생성
	MapManager MyMapManager;
	//맵 생성
	MyMapManager.GenerateBSPMap(6);
	//맵 출력
	MyMapManager.PrintMap();

	return 0;
}