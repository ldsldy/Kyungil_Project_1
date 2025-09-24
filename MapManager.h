#pragma once
#include "BSPGenerator.h"
#include "GameManager.h"
#include "Map.h"

//�˰���� ���� ó���� ����
class MapManager
{
public:
	MapManager()
	{
		CurrentMap = new Map();
		//���� ����ϰ� �޸𸮸� ���� �Դ� ������ ĳ��
		MapLength = CurrentMap->GetMapLength();
		RegionSize = CurrentMap->GetRegionSize();
		MapManagerToken = 0;
	}
	~MapManager()
	{
		delete CurrentMap;
		delete BSPGen;
	}

	//�� ����
	void GenerateMap(unsigned int MinRoomSize = 6);
	
	//GameManager���� Map������ �Լ��� ��� ����
	Map* GetMap() { return CurrentMap; }

	//����� �Լ�
	void PrintMap() const;



	//=======�����============//
	//�� ���(����׿�)
	void PrintTestMap() const;

	//���� �� �κ� ���(����׿�)
	void PrintRegionMap() const;

	void PrintMapInfo() const;

private:
	//���ҵ� ������ ��ū ��ġ ��ġ ����
	//�÷��̾� ���� ���� ��ġ ����
	//BFS�� �̿��� ��� Ž�� �� ����Ÿ� ���
	//Ż�ⱸ �ڵ� ��ġ
	//��ū ����(���ӸŴ������� ��ū�� ���� ������ �޾� ��ū ����)

	

	int MapLength;
	int RegionSize;
	int MapManagerToken; //�ʿ� ��ġ�� ��ū ����

	Map* CurrentMap;
	BSPGenerator* BSPGen;
};

