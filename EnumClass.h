#pragma once

enum class CellType
{
	Wall,
	Floor,
	Token,
	Player,
	Exit
};

enum class Direction
{
	Up,
	Down,
	Left,
	Right,
	Default
};