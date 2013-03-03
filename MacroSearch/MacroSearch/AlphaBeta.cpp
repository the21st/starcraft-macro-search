#pragma once

#include "AlphaBeta.h"

AlphaBeta::AlphaBeta(void)
{
}


AlphaBeta::~AlphaBeta(void)
{
}

AlphaBetaScore AlphaBeta::Search(Node node, int depth, AlphaBetaScore alpha, AlphaBetaScore beta)
{
	if (depth == 0 || node.IsTerminal())
	{
		return node.Eval();
	}

	auto maxPlayer = node.IsMaxPlayerMove();

	if (maxPlayer)
	{
		for each (auto child in node.GetChildren())
		{
			alpha = std::max(alpha, Search(child, depth-1, alpha, beta));
			if (beta <= alpha)
			{
				// Beta cut-off
				break;
			}
		}
		return alpha;
	}
	else
	{
		for each (auto child in node.GetChildren())
		{
			beta = std::min(beta, Search(child, depth-1, alpha, beta));
			if (beta <= alpha)
			{
				// Alpha cut-off
				break;
			}
		}
		return beta;
	}
}
