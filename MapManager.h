#pragma once
#include "BSPGenerator.h"
#include <iostream>

using namespace std;

//알고리즘과 로직 처리에 집중
class MapManager : public BSPGenerator
{
private:
	int MapLengthFromMap;
	int MapManagerToken; //맵에 설치된 토큰 갯수
	

public:
	MapManager();
	virtual ~MapManager()
	{
		cout << "MapManager Destructed\n";
	}

	virtual void Init() override;

	void PrintMap() const;
		
	//GameManager에서 Map정보와 함수를 얻기 위함
	int GetMapLengthFromMap();

	//=======디버깅============//
	void PrintMapInfo() const;
};

