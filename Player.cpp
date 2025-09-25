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
