#include "GameManager.h"
#include "Map.h"
#include "BSPGenerator.h"
#include <iostream>

//���� �Ű������� ���� ������, const�� �� ��ȣ��, �ΰ��� �Բ� ���°� ����
//void PrintMapInTest(Map* InMap);

int main()
{
	cout << "===========�� �׽�Ʈ==========\n";
	
	//���� �Ŵ��� ����
	GameManager MyGameManger;
	MyGameManger.Run();

	////�� ����
	/*Map MyMap(64, 64);
	BSPGenerator GameMapGenerator;

	GameMapGenerator.GenerateMap(MyMap, 6, 16);

	MyMap.Print(Point(2, 2));*/

	return 0;
}
