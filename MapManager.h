#pragma once
#include "BSPGenerator.h"
#include <iostream>

using namespace std;

//�˰���� ���� ó���� ����
class MapManager : public BSPGenerator
{
private:
	int MapLengthFromMap;
	int MapManagerToken; //�ʿ� ��ġ�� ��ū ����
	

public:
	MapManager();
	virtual ~MapManager()
	{
		cout << "MapManager Destructed\n";
	}

	virtual void Init() override;

	void PrintMap() const;
		
	//GameManager���� Map������ �Լ��� ��� ����
	int GetMapLengthFromMap();

	//=======�����============//
	void PrintMapInfo() const;
};

