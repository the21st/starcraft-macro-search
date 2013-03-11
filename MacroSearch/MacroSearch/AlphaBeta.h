#pragma once

#include "ISearchNode.h"

class AlphaBeta
{
public:

	AlphaBeta(void);
	~AlphaBeta(void);

	AlphaBetaScore Search(ISearchNode & state, int depth, float alpha, float beta);

	AlphaBetaScore SearchUsingRecursion(ISearchNode & node, int depth, AlphaBetaScore alpha, AlphaBetaScore beta);

};

