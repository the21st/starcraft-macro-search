#pragma once

#include "AlphaBeta.h"

AlphaBeta::AlphaBeta(void)
{
}


AlphaBeta::~AlphaBeta(void)
{
}

AlphaBetaScore AlphaBeta::Search(ISearchNode & node, int depth, AlphaBetaScore alpha, AlphaBetaScore beta)
{
	if (depth == 0 || node.IsTerminal())
	{
		auto result = node.Eval();
		return result;
	}

	auto maxPlayer = node.IsMaxPlayerMove();

	if (maxPlayer)
	{
		auto children = node.GetChildren();
		for each (auto child in children)
		{
			alpha = std::max(alpha, Search(*child, depth-1, alpha, beta));
			if (beta <= alpha)
			{
				// Beta cut-off
				break;
			}
		}

		for (size_t i = 0; i < children.size(); i++)
		{
			delete children[i];
		}

		return alpha;
	}
	else
	{
		auto children = node.GetChildren();
		for each (auto child in children)
		{
			beta = std::min(beta, Search(*child, depth-1, alpha, beta));
			if (beta <= alpha)
			{
				// Alpha cut-off
				break;
			}
		}

		for (size_t i = 0; i < children.size(); i++)
		{
			delete children[i];
		}

		return beta;
	}
}
