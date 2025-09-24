#pragma once
#include "Point.h"
#include "EnumClass.h"
#include "GameManger.h"

GameManager* CurrentGameManager;

class Player
{
public:
	Player()
	{
		//게임 매니저에게서 맵 매니저가 생성한 플레이어 생성 위치를 받아와서 초기화
	}

	//게임 매니저가 플레이어 위치를 요청할 때
	inline Point GetPlayerPose() const { return PlayerPos; }
	

	//적과 충돌(게임오버 or 체력감소)
	//아이템 획득(일정시간 맵 전체 보여줌, 적 정지) => 게임매니저에 알림
	Direction GetMoveDirection();

private:
	void Move(Direction MoveDirection);
	//키를 누르면 이동 (이동 속도 조정)

	/// <summary>
	/// 이동할 방향을 결정하는 함수 => 실제 이동 함수로 전달
	/// </summary>
	/// <returns>이동할 방향의 Enum</returns>

	//현재 위치
	Point PlayerPos;
	int WalkSpeed; //이동 속도
};

