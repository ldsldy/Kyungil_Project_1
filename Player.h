#pragma once
#include "Point.h"
#include "EnumClass.h"

class Map;

class Player
{
private:
	//플레이어 위치
	Point Position;

public:
	Player():Position(0,0){}

	inline const Point GetPosition() const { return Position; }
	inline void SetPosition(const Point& InPos) { Position = InPos; }
	
	// <summary>
	/// 플레이어의 이동 방향을 입력받아 반환하는 함수
	/// </summary>
	/// <returns>이동할 방향의 Enum</returns>
	Direction GetInputDirection();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="InDirection"></param>
	/// <param name="InMap"></param>
	/// <returns></returns>
	bool Move(Direction InDirection, Map& InMap);

	bool DetectedTokenCollision(Map& InMap);
};

//자기 위치를 맵에 뿌리고
//이동 방향을 입력받아 이동
//토큰 충돌 감지
//출구 충돌 감지
