#include "Player.h"
#include <iostream>
#include <conio.h>
#include "GameManager.h"

using namespace std;

Direction Player::GetMoveDirection()
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
	return Direction::Default;
}

void Player::Move(Direction MoveDirection)
{
	if (CurrentGameManager->CanPlayerMove())
	{
		if (MoveDirection == Direction::Up)
			switch (MoveDirection)
			{
			case Direction::Up:
				PlayerPos.y = PlayerPos.y - 1;
				break;
			case Direction::Down:
				PlayerPos.y = PlayerPos.y + 1;
				break;
			case Direction::Left:
				PlayerPos.x = PlayerPos.x - 1;
				break;
			case Direction::Right:
				PlayerPos.x = PlayerPos.x + 1;
				break;
			case Direction::Default:
				break;
			}
	}
}
