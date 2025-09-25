#pragma once

enum class CellType
{
	Wall,
	Floor,
	Token,
	Start,
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