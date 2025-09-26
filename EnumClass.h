#pragma once

enum class CellType
{
	Wall,
	Floor,
	Token,
	Enemy,
	Exit,
	Start,
};

enum class Direction
{
	Up,
	Down,
	Left,
	Right,
	None
};

enum class EnemyState
{
	Patrol,
	Chasing,
	Exhausted
};
enum class GameState
{
	Playing,
	GameOver,
	Clear
};