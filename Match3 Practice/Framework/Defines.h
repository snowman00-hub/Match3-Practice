#pragma once

enum class SortingLayers 
{
	Background,
	Foreground,
	UI,
};

enum class Origins
{
	TL, TC, TR,	// 0 1 2
	ML, MC, MR,	// 3 4 5
	BL, BC, BR, // 6 7 8
	Custom
};

enum class SceneIds
{
	None = -1,
	Start,
	Lobby,
	Stage1,
	Stage2,
	Stage3,
	Game,
	Dev1,
	Dev2,
	Count,
};

enum class Sides
{
	Left,
	Right,
	None,
};

enum class GameState
{
	Idle,
	Swap,
	Animation,
	MatchCheck,
	Remove,
	Drop
};

enum class BlockTypes
{
	None = -1,
	Jem,
	Wall,
	RedJem = 2,
	YellowJem,
	GreenJem,
	BlueJem,
	Diamond,
	Emerald = 7,
};

enum class TileTypes
{
	None = -1,
	Default,
	Painted,
};