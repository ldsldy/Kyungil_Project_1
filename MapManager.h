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
	int MapManagerToken; //�ʿ� ��ġ�� ��ū ����
	
	inline Point GetPlayer() const { return BSPGen->GetPlayerSpawn(); }

public:
	MapManager() : ManagerMap(new Map), BSPGen(new BSPGenerator)
	{
		cout << "MapManager Constructed\n";
		MapLength = ManagerMap->GetMapLength();
		BSPGen->GenerateMap(*ManagerMap, 10);
	}
	~MapManager()
	{
		delete ManagerMap;
		delete BSPGen;
		cout << "MapManager Destructed\n";
	}
	
	//BSP���� �÷��̾� ���� ��ġ�� �޾ƿ� Map�� �ݿ�
	void PlayerSpawnPoint();
	
	//GameManager���� Map������ �Լ��� ��� ����
	Map* GetMap() { return ManagerMap;}

	//����� �Լ�
	void PrintMap() const;

	//=======�����============//
	void PrintMapInfo() const;
};

