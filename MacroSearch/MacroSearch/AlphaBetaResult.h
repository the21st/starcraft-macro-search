#pragma once

#include "Common.h"
#include <list>
#include "Action.h"
#include "GameState.h"

namespace MacroSearch
{
	struct AlphaBetaResult
	{
		// the score of the utility function
		AlphaBetaScore Score;

		// what the first action leading to that utility function is
		Action BestAction;

		// the game state corresponding to this utility
		GameState FinalGameState;

		bool operator <	(const AlphaBetaResult & otherResult) const { return Score < otherResult.Score; }
		bool operator >	(const AlphaBetaResult & otherResult) const { return Score > otherResult.Score; }

		AlphaBetaResult() { }

		AlphaBetaResult(AlphaBetaScore score)
			:Score(score)
		{

		}
	};
}