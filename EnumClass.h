#pragma once

enum class CellType
{
	Wall,
	Floor,
	Item,
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