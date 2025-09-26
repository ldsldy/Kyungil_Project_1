#include "GameManager.h"
#include "Map.h"
#include "BSPGenerator.h"
#include <iostream>
#include <windows.h>

//참조 매개변수는 복사 방지용, const는 값 보호용, 두개를 함께 쓰는게 좋음
//void PrintMapInTest(Map* InMap);

void setConsoleSize(int width, int height) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 버퍼 크기 설정
    COORD bufferSize = { width, height };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // 윈도우 크기 설정
    SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

int main()
{	
    setConsoleSize(100, 50);
	//게임 매니저 생성
	GameManager MyGameManger;
	MyGameManger.Run();


	return 0;
}
