#include "GameManager.h"
#include "Map.h"
#include "BSPGenerator.h"
#include <iostream>
#include <windows.h>

//���� �Ű������� ���� ������, const�� �� ��ȣ��, �ΰ��� �Բ� ���°� ����
//void PrintMapInTest(Map* InMap);

void setConsoleSize(int width, int height) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // ���� ũ�� ����
    COORD bufferSize = { width, height };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // ������ ũ�� ����
    SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

int main()
{	
    setConsoleSize(100, 50);
	//���� �Ŵ��� ����
	GameManager MyGameManger;
	MyGameManger.Run();


	return 0;
}
