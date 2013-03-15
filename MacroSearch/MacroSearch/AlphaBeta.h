#pragma once

#include "ISearchNode.h"

class AlphaBeta
{
public:

	AlphaBeta(void);
	~AlphaBeta(void);

	AlphaBetaScore SearchIterative(ISearchNode * state, int depth, float alpha, float beta);

	AlphaBetaScore SearchRecursive(ISearchNode & node, int depth, AlphaBetaScore alpha, AlphaBetaScore beta);

};

