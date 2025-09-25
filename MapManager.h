#pragma once
#include "BSPGenerator.h"
#include "GameManager.h"
#include "Map.h"

#include <iostream>

using namespace std;

extern class Map;
extern class BSPGenerator;

//�˰���� ���� ó���� ����
class MapManager
{
private:
	//���ҵ� ������ ��ū ��ġ ��ġ ����
	//�÷��̾� ���� ���� ��ġ ����
	//BFS�� �̿��� ��� Ž�� �� ����Ÿ� ���
	//Ż�ⱸ �ڵ� ��ġ
	//��ū ����(���ӸŴ������� ��ū�� ���� ������ �޾� ��ū ����)
	Map* ManagerMap;
	BSPGenerator* BSPGen;
	int MapLength;
	int RegionSize;
	int MapManagerToken; //�ʿ� ��ġ�� ��ū ����
public:
	MapManager() : ManagerMap(new Map), BSPGen(new BSPGenerator)
	{
		BSPGen->GenerateMap(*ManagerMap, 6);
	}
	~MapManager()
	{
		delete ManagerMap;
		delete BSPGen;
		cout << "MapManager Destructed\n";
	}

	//�� ����
	//void GenerateBSPMap(unsigned int MinRoomSize = 6);
	
	//GameManager���� Map������ �Լ��� ��� ����
	Map* GetMap() { return ManagerMap;}

	//����� �Լ�
	void PrintMap() const;

	//=======�����============//
	//�� ���(����׿�)
	void PrintTestMap() const;

	//���� �� �κ� ���(����׿�)
	void PrintRegionMap() const;

	void PrintMapInfo() const;

	void DataCaching(); //���� ����ϰ� �޸𸮸� ���� �Դ� ������ ĳ��
};

