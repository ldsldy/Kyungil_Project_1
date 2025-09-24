#pragma once
#include "BSPGenerator.h"
#include "GameManger.h"
#include "Map.h"

//������ ������ ����
GameManager* CurrentGameManager;
BSPGenerator* BSPGen;

//�˰���� ���� ó���� ����
class MapManager
{
public:
	MapManager()
	{
		CurrentMap = new Map();
		//���� ����ϰ� �޸𸮸� ���� �Դ� ������ ĳ��
		MapSize = CurrentMap->GetMapSize();
		RegionSize = CurrentMap->GetRegionSize();

		//BSPGenerator�� Map �� ���� ����
	}

	//GameManager���� Map������ �Լ��� ��� ����
	Map* GetMap() { return CurrentMap; }

private:
	//BSP�˰����� ���� �� ���� �� ��ġ��
	//���ҵ� ������ ��ū ��ġ ��ġ ����
	//�÷��̾� ���� ���� ��ġ ����
	//BFS�� �̿��� ��� Ž�� �� ����Ÿ� ���
	//Ż�ⱸ �ڵ� ��ġ
	//�� ��ü ���μ��� ����
	//��ū ����(���ӸŴ������� ��ū�� ���� ������ �޾� ��ū ����)

	//�� ���(����׿�)
	void PrintTestMap() const;

	//���� �� �κ� ���(����׿�)
	void PrintRegionMap() const;

	int MapSize;
	int RegionSize;
	int TokenCount;

	Map* CurrentMap;
};

