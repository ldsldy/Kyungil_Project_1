#include "GameManger.h"

void GameManager::Run()
{
	Update();
}

bool GameManager::CanPlayerMove()
{
	// 플레이어가 가고 싶은 좌표를 미리 확인할 좌표 생성
	Point PrecUserPos = UserPos;
	if (UserDirection == Direction::Up)
	{
		PrecUserPos.y = UserPos.y - 1;
	}
	if (UserDirection == Direction::Down)
	{
		PrecUserPos.y = UserPos.y + 1;
	}
	if (UserDirection == Direction::Left)
	{
		PrecUserPos.x = UserPos.x - 1;
	}
	if (UserDirection == Direction::Right)
	{
		PrecUserPos.x = UserPos.x + 1;
	}
	
	// 플레이어가 가고 싶은 좌표가 벽이나 갈수가 없는 길이라면 false
	if (CurrentMapManager->GetMap()->IsWall(PrecUserPos.x, PrecUserPos.y)
		|| !(CurrentMapManager->GetMap()->IsValidPosition(PrecUserPos.x, PrecUserPos.y)))
	{
		return false;
	}
	else
	{
		return true;
	}
}
