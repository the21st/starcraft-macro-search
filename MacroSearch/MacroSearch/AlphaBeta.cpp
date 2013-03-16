#pragma once

#include "AlphaBeta.h"


AlphaBeta::AlphaBeta(void)
{
}


AlphaBeta::~AlphaBeta(void)
{
}

AlphaBetaScore AlphaBeta::SearchIterative(ISearchNode * node, int depth, AlphaBetaScore alpha, AlphaBetaScore beta)
{
	// (Second rule)
	AlphaBetaScore returnValue = 0;

	// (Third rule)
	std::stack<AlphaBetaSnapshot> recursionStack;

	// (Fourth rule)
	AlphaBetaSnapshot initialSnapshot;
	initialSnapshot.Node = node;
	initialSnapshot.Depth = depth;
	initialSnapshot.Alpha = alpha;
	initialSnapshot.Beta = beta;
	initialSnapshot.Stage = 0;
	initialSnapshot.ChildIndex = -1;

	recursionStack.push(initialSnapshot);

	// (Fifth rule)
	while (!recursionStack.empty())
	{
		auto currentSnapshot = recursionStack.top();
		recursionStack.pop();

		// (Sixth rule)
		switch (currentSnapshot.Stage)
		{
		case 0:
			{
				if (currentSnapshot.Depth == 0 || currentSnapshot.Node->IsTerminal())
				{
					returnValue = currentSnapshot.Node->Eval();
					continue;
				}

				currentSnapshot.Children = currentSnapshot.Node->GenerateChildren();
				currentSnapshot.ChildIndex = 0;

				PushNextChild(currentSnapshot, recursionStack);

				continue;

				break;
			}
		case 1:
			{
				auto childSearchResult = returnValue;

				if (currentSnapshot.Node->IsMaxPlayerMove())
				{
					currentSnapshot.Alpha = std::max(currentSnapshot.Alpha, childSearchResult);
				}
				else
				{
					currentSnapshot.Beta = std::min(currentSnapshot.Beta, childSearchResult);
				}

				currentSnapshot.ChildIndex++;
				if (currentSnapshot.ChildIndex < currentSnapshot.Children.size())
				{
					// PRUNE ?
					if (currentSnapshot.Beta > currentSnapshot.Alpha)
					{
						// NOT PRUNED ! push next child

						PushNextChild(currentSnapshot, recursionStack);

						continue;
					}
					else
					{
						// PRUNED !

						returnValue = FinishUp(currentSnapshot);

						continue;
					}
				}
				else
				{
					returnValue = FinishUp(currentSnapshot);

					continue;
				}

				break;

			}

		default:
			throw 1;
			break;
		}
	}

	// (Second rule)
	return returnValue;
}

AlphaBetaScore AlphaBeta::SearchRecursive(ISearchNode & node, int depth, AlphaBetaScore alpha, AlphaBetaScore beta)
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
		auto childSearchResult = SearchRecursive(*child, depth-1, alpha, beta);

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

void AlphaBeta::PushNextChild( AlphaBetaSnapshot &currentSnapshot, std::stack<AlphaBetaSnapshot> &recursionStack )
{
	// (Tenth rule)
	// current snapshot need to process after
	currentSnapshot.Stage = 1;
	// returning from the recursive call
	// this MUST pushed into stack before 
	recursionStack.push(currentSnapshot);

	// Create a new snapshot for calling itself
	// "emulated" call: Search(child, currentSnapshot.Depth - 1, currentSnapshot.Alpha, currentSnapshot.Beta)
	AlphaBetaSnapshot nextSnapshot;
	nextSnapshot.Node = currentSnapshot.Children[currentSnapshot.ChildIndex];
	nextSnapshot.Depth = currentSnapshot.Depth - 1;
	nextSnapshot.Alpha = currentSnapshot.Alpha;
	nextSnapshot.Beta = currentSnapshot.Beta;

	// since it will start from the beginning of the function, give the initial stage
	nextSnapshot.Stage = 0;
	recursionStack.push(nextSnapshot);
}

AlphaBetaScore AlphaBeta::FinishUp( AlphaBetaSnapshot &currentSnapshot )
{
	for (size_t i = 0; i < currentSnapshot.Children.size(); i++)
	{
		delete currentSnapshot.Children[i];
	}

	if (currentSnapshot.Node->IsMaxPlayerMove())
	{
		return currentSnapshot.Alpha;
	}
	else
	{
		return currentSnapshot.Beta;
	}
}
