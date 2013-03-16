#pragma once

#include <stack>
#include "ISearchNode.h"

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

class AlphaBeta
{
public:

	AlphaBeta(void);
	~AlphaBeta(void);

	// made using the recursion to explicit stack guide at
	// http://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and
	AlphaBetaScore SearchIterative(ISearchNode * state, int depth, float alpha, float beta);

	AlphaBetaScore SearchRecursive(ISearchNode & node, int depth, AlphaBetaScore alpha, AlphaBetaScore beta);

private:

	void PushNextChild( AlphaBetaSnapshot &currentSnapshot, std::stack<AlphaBetaSnapshot> &recursionStack );

	AlphaBetaScore FinishUp( AlphaBetaSnapshot &currentSnapshot );
};

