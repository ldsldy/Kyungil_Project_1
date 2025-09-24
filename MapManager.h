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
		MapLength = CurrentMap->GetMapLength();
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

	int MapLength;
	int RegionSize;
	int TokenCount;

	Map* CurrentMap;
};

