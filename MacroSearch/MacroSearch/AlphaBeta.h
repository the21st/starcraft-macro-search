#pragma once

#include "Node.h"

class AlphaBeta
{
public:
	AlphaBeta(void);
	~AlphaBeta(void);

	AlphaBetaScore Search(Node state, int depth, float alpha, float beta);
};

