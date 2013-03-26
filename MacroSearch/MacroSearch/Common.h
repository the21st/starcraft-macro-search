#pragma once

#include <BWAPI.h>
#include <assert.h>

typedef float AlphaBetaScore;

// time = frame count
typedef int GameTime;

namespace MacroSearch
{
	// PLAYERS IN THE GAME
	namespace Players
	{
		enum { Player_One = 0, Player_Two = 1 };
	}
}