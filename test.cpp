#include "GameManager.h"
#include <iostream>

//���� �Ű������� ���� ������, const�� �� ��ȣ��, �ΰ��� �Բ� ���°� ����
//void PrintMapInTest(Map* InMap);

int main()
{
	cout << "===========�� �׽�Ʈ==========\n";
	
	//���� �Ŵ��� ����
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
//				cout << "��"; break;
//			case CellType::Floor: 
//				cout.width(2);
//				cout << " "; break;
//			case CellType::Token:
//				cout.width(2);
//				cout << "��"; break;
//			case CellType::Exit: 
//				cout.width(2);
//				cout << "E"; break;
//			default:cout << "?"; break;
//			}
//		}
//		cout << endl;
//	}
//}