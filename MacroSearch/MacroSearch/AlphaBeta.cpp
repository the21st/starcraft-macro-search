#pragma once

#include <stack>
#include "AlphaBeta.h"

// made using the recursion to explicit stack guide at
// http://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and

// (First rule)
struct AlphaBetaSnapshot
{
	// parameters
	ISearchNode * Node;
	int Depth;
	AlphaBetaScore Alpha;
	AlphaBetaScore Beta;

	// local variables
	std::vector<ISearchNode*> Children;

	// control variables
	int Stage;
	int ChildIndex;
};

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
	initialSnapshot.Stage = 0; // set the value as initial stage
	initialSnapshot.ChildIndex = -1; // set the value as initial stage

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

				// (Tenth rule)
				// current snapshot need to process after
				currentSnapshot.Stage = 1;
				currentSnapshot.ChildIndex = 0;
				// returning from the recursive call
				// this MUST pushed into stack before 
				recursionStack.push(currentSnapshot);
			
				// Create a new snapshot for calling itself
				// Search(child, currentSnapshot.Depth - 1, currentSnapshot.Alpha, currentSnapshot.Beta)
				AlphaBetaSnapshot newSnapshot;
				newSnapshot.Node = currentSnapshot.Children[currentSnapshot.ChildIndex];
				newSnapshot.Depth = currentSnapshot.Depth - 1;
				newSnapshot.Alpha = currentSnapshot.Alpha;
				newSnapshot.Beta = currentSnapshot.Beta;

				// since it will start from the beginning of the function, give the initial stage
				newSnapshot.Stage = 0;
				recursionStack.push(newSnapshot);
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

						// (Tenth rule)
						// current snapshot need to process after
						currentSnapshot.Stage = 1;
						// returning from the recursive call
						// this MUST pushed into stack before 
						recursionStack.push(currentSnapshot);

						// Create a new snapshot for calling itself
						// Search(child, currentSnapshot.Depth - 1, currentSnapshot.Alpha, currentSnapshot.Beta)
						AlphaBetaSnapshot nextSnapshot;
						nextSnapshot.Node = currentSnapshot.Children[currentSnapshot.ChildIndex];
						nextSnapshot.Depth = currentSnapshot.Depth - 1;
						nextSnapshot.Alpha = currentSnapshot.Alpha;
						nextSnapshot.Beta = currentSnapshot.Beta;

						// since it will start from the beginning of the function, give the initial stage
						nextSnapshot.Stage = 0;
						recursionStack.push(nextSnapshot);
						continue;
					}
					else
					{
						// PRUNED !

						for (size_t i = 0; i < currentSnapshot.Children.size(); i++)
						{
							delete currentSnapshot.Children[i];
						}

						if (currentSnapshot.Node->IsMaxPlayerMove())
						{
							returnValue = currentSnapshot.Alpha;
							continue;
						}
						else
						{
							returnValue = currentSnapshot.Beta;
							continue;
						}
					}
				}
				else
				{
					for (size_t i = 0; i < currentSnapshot.Children.size(); i++)
					{
						delete currentSnapshot.Children[i];
					}

					if (currentSnapshot.Node->IsMaxPlayerMove())
					{
						returnValue = currentSnapshot.Alpha;
						continue;
					}
					else
					{
						returnValue = currentSnapshot.Beta;
						continue;
					}
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
