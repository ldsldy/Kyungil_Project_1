#include "Map.h"
//���� å��
//���� �Ŵ����� ������

//�÷��̾�, ��, ���� ���� �Ŵ������� ������ �ߴ��� �˸��� ���� �Ŵ����� ó���ؼ�
//�ٸ� Ŭ������ �Ѹ���.
int main()
{
	Map testMap(25, 25);
	testMap.Init();
	testMap.PrintTestMap();
	testMap.PrintRegionMap();

	return 0;
}