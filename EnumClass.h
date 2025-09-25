#pragma once

enum class CellType
{
	Wall,
	Floor,
	Token,
	Enemy,
	Player,
	Exit,
	Start
};

enum class Direction
{
	Up,
	Down,
	Left,
	Right,
	None
};

enum class GameState
{
	Playing,
	GameOver,
	Clear
};