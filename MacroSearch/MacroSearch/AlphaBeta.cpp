#pragma once

#include "AlphaBeta.h"
#include "boost\foreach.hpp"
#include "Node.h"

using namespace MacroSearch;

AlphaBeta::AlphaBeta(void)
{
}


AlphaBeta::~AlphaBeta(void)
{
}

AlphaBetaResult AlphaBeta::SearchRecursive(ISearchNode & node, int depth, AlphaBetaResult alpha, AlphaBetaResult beta)
{
	if (depth == 0 || node.IsTerminal())
	{
		// if we exceeded max depth or the state is terminal, just use an evaluation function

		AlphaBetaResult result;
		result.Score = node.Eval();
		result.BestAction = node.GeneratingAction;

		// this is a quick, ugly hack to look at the last optimal game state in the game tree
		result.FinalGameState = static_cast<Node*>(&node)->_gameState;
		return result;
	}

	bool maxPlayer = node.IsMaxPlayerMove();

	// generate the children of the node
	std::vector<ISearchNode*> children = node.GenerateChildren();

	// search them, depth-first
	BOOST_FOREACH (ISearchNode *child, children)
	{
		AlphaBetaResult childSearchResult = SearchRecursive(*child, depth - 1, alpha, beta);
		childSearchResult.BestAction = child->GeneratingAction;

		if (maxPlayer)
		{
			alpha = std::max(alpha, childSearchResult);
		}
		else
		{
			beta = std::min(beta, childSearchResult);
		}

		if (beta.Score <= alpha.Score)
		{
			// alpha or beta prune
			break;
		}
	}

	// delete the children (only if this was so easy in real life)
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

AlphaBetaResult AlphaBeta::SearchIterative(ISearchNode * node, int depth, AlphaBetaScore alpha, AlphaBetaScore beta)
{
	// (Second rule)
	AlphaBetaResult returnValue;

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
		AlphaBetaSnapshot currentSnapshot = recursionStack.top();
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
				AlphaBetaResult childSearchResult = returnValue;

				if (currentSnapshot.Node->IsMaxPlayerMove())
				{
					currentSnapshot.Alpha = std::max(currentSnapshot.Alpha, childSearchResult.Score);
				}
				else
				{
					currentSnapshot.Beta = std::min(currentSnapshot.Beta, childSearchResult.Score);
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

						returnValue.Score = FinishUp(currentSnapshot);

						continue;
					}
				}
				else
				{
					returnValue.Score = FinishUp(currentSnapshot);

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

void AlphaBeta::PushNextChild( AlphaBetaSnapshot &currentSnapshot, std::stack<AlphaBetaSnapshot> &recursionStack )
{
	// (Tenth rule)
	// current snapshot need to process after returning from the recursive call
	currentSnapshot.Stage = 1;
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
