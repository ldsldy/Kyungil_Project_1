#include "MapManager.h"
#include <iostream>
//���� å��
//���� �Ŵ����� ������

//�÷��̾�, ��, ���� ���� �Ŵ������� ������ �ߴ��� �˸��� ���� �Ŵ����� ó���ؼ�
//�ٸ� Ŭ������ �Ѹ���.
int main()
{
	cout << "====�� ������ �׽�Ʈ==========\n";
	//�� �Ŵ��� ����
	MapManager MyMapManager;
	//�� ����
	MyMapManager.GenerateBSPMap(6);
	//�� ���
	MyMapManager.PrintMap();

	return 0;
}