#include "Player.h"
#include "Map.h"
#include <iostream>
#include <conio.h>

using namespace std;

Direction Player::GetInputDirection()
{
	char MoveInput;
	MoveInput = _getch();

	if (MoveInput == 'w' || MoveInput == 'W')
	{
		return Direction::Up;
	}
	if (MoveInput == 's' || MoveInput == 'S')
	{
		return Direction::Down;
	}
	if (MoveInput == 'a' || MoveInput == 'A')
	{
		return Direction::Left;
	}
	if (MoveInput == 'd' || MoveInput == 'D')
	{
		return Direction::Right;
	}
	return Direction::None;
}

bool Player::Move(Direction InDirection, Map& InMap)
{
	Point NewPosition = Position;

	if (InDirection == Direction::Up)
	{
		NewPosition.y = NewPosition.y - 1;
	}
	if (InDirection == Direction::Down)
	{
		NewPosition.y = NewPosition.y + 1;
	}
	if (InDirection == Direction::Left)
	{
		NewPosition.x = NewPosition.x - 1;
	}
	if (InDirection == Direction::Right)
	{
		NewPosition.x = NewPosition.x + 1;
	}

	if(InMap.IsWalkable(NewPosition.x, NewPosition.y))
	{
		Position = NewPosition;
		return true;
	}

	return false;
}

bool Player::DetectedTokenCollision(Map& InMap)
{
	//플레이어 위치에 토큰이 있다면 토큰을 없애고 true 반환
	if (InMap.GetCell(Position.x, Position.y) == CellType::Token)
	{
		InMap.SetCell(Position.x, Position.y, CellType::Floor);
		return true;
	}
	return false;
}