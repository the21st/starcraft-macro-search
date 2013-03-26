#pragma once

#include "Common.h"
#include <list>
#include "Action.h"

namespace MacroSearch
{
	struct AlphaBetaResult
	{
		AlphaBetaScore Score;
		Action BestAction;

		bool operator <	(const AlphaBetaResult & otherResult) const { return Score < otherResult.Score; }
		bool operator >	(const AlphaBetaResult & otherResult) const { return Score > otherResult.Score; }

		AlphaBetaResult() { }

		AlphaBetaResult(AlphaBetaScore score)
			:Score(score)
		{

		}

		//AlphaBetaResult(AlphaBetaScore score, std::vector<BWAPI::UnitType> production)
		//	:
		//	Score(score),
		//	Production(production)
		//{

		//}
	};
}