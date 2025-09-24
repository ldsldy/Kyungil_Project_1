#pragma once
#include "BSPGenerator.h"
#include "GameManager.h"
#include "Map.h"

extern class Map;
extern class BSPGenerator;

//�˰���� ���� ó���� ����
class MapManager
{
public:
	MapManager() : ManagerMap(new Map), BSPGen(new BSPGenerator){}
	~MapManager()
	{
		delete ManagerMap;
		delete BSPGen;
	}

	//�� ����
	void GenerateBSPMap(unsigned int MinRoomSize = 6);
	
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
private:
	//���ҵ� ������ ��ū ��ġ ��ġ ����
	//�÷��̾� ���� ���� ��ġ ����
	//BFS�� �̿��� ��� Ž�� �� ����Ÿ� ���
	//Ż�ⱸ �ڵ� ��ġ
	//��ū ����(���ӸŴ������� ��ū�� ���� ������ �޾� ��ū ����)
	Map* ManagerMap;
	BSPGenerator* BSPGen = new BSPGenerator;
	int MapLength;
	int RegionSize;
	int MapManagerToken; //�ʿ� ��ġ�� ��ū ����
};

