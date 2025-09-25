#pragma once
#include "Point.h"
#include "EnumClass.h"

extern class GameManager;

class Player
{
public:
	Player(){
		PlayerPos = (0, 0);
	}

	//게임 매니저가 플레이어 위치를 요청할 때
	inline Point GetPlayerPose() const { return PlayerPos; }
	inline Point GetPlayerX() const { return PlayerPos.x; }
	inline Point GetPlayerY() const { return PlayerPos.y; }
	/// <summary>
	/// 이동할 방향을 결정하는 함수 => 실제 이동 함수로 전달
	/// </summary>
	/// <returns>이동할 방향의 Enum</returns>
	Direction GetMoveDirection();

	inline void SetPositionX(int InX) { PlayerPos.x = InX; }
	inline void SetPositionY(int InY) { PlayerPos.y = InY; }
	inline void SetPosition(Point InPos) { PlayerPos = InPos; }

private:
	//현재 위치
	Point PlayerPos;
	int WalkSpeed;	//이동 속도
	GameManager* CurrentGameManager;
};

