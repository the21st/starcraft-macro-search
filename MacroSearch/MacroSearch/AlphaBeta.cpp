#pragma once

#include <stack>
#include "AlphaBeta.h"

// made using the recursion to explicit stack guide at
// http://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and

// (First rule)
struct AlphaBetaSnapshot
{
	int Depth;
	AlphaBetaScore Alpha;
	AlphaBetaScore Beta;

	int Stage;
};

AlphaBeta::AlphaBeta(void)
{
}


AlphaBeta::~AlphaBeta(void)
{
}

AlphaBetaScore AlphaBeta::Search(ISearchNode & node, int depth, AlphaBetaScore alpha, AlphaBetaScore beta)
{
	// (Second rule)
	AlphaBetaScore returnValue = 0;

	// (Third rule)
	std::stack<AlphaBetaSnapshot> recursionStack;

	// (Fourth rule)
	AlphaBetaSnapshot initialSnapshot;
	initialSnapshot.Depth = depth;
	initialSnapshot.Alpha = alpha;
	initialSnapshot.Beta = beta;
	initialSnapshot.Stage = 0; // set the value as initial stage

	recursionStack.push(initialSnapshot);

	// (Fifth rule)
	while (!recursionStack.empty())
	{
		auto currentSnapshot = recursionStack.top();
		recursionStack.pop();

		int depth = currentSnapshot.Depth;
		//ISearchNode& node = currentParams.Node;
		AlphaBetaScore alpha = currentSnapshot.Alpha;
		AlphaBetaScore beta = currentSnapshot.Beta;

		if (depth == 0 || node.IsTerminal())
		{
			auto result = node.Eval();
			return result;
		}

		auto maxPlayer = node.IsMaxPlayerMove();

		if (maxPlayer)
		{
			auto children = node.GenerateChildren();
			for each (auto child in children)
			{
				alpha = std::max(alpha, Search(*child, depth-1, alpha, beta));
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
			auto children = node.GenerateChildren();
			for each (auto child in children)
			{
				beta = std::min(beta, Search(*child, depth-1, alpha, beta));
				if (beta <= alpha)
				{
					// Alpha cut-off
					break;
				}
			}

			return beta;
		}
	}

	// (Second rule)
	return returnValue;
}

AlphaBetaScore AlphaBeta::SearchUsingRecursion(ISearchNode & node, int depth, AlphaBetaScore alpha, AlphaBetaScore beta)
{
	if (depth == 0 || node.IsTerminal())
	{
		auto result = node.Eval();
		return result;
	}

	auto maxPlayer = node.IsMaxPlayerMove();

	auto children = node.GenerateChildren();
	for each (auto child in children)
	{
		auto childSearchResult = SearchUsingRecursion(*child, depth-1, alpha, beta);

		if (maxPlayer)
		{
			alpha = std::max(alpha, childSearchResult);
		}
		else
		{
			beta = std::min(beta, childSearchResult);
		}

		if (beta <= alpha)
		{
			// alpha or beta cut-off
			break;
		}
	}

	for (size_t i = 0; i < children.size(); i++)
	{
		delete children[i];
	}

	if (maxPlayer)
	{
		return alpha;
	}
	else
	{
		return beta;
	}
}
