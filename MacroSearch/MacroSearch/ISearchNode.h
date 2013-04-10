#pragma once

#include <vector>
#include "Common.h"
#include "AlphaBetaResult.h"
#include "Action.h"

class ISearchNode
{
public:

	virtual ~ISearchNode() {}

	// Gets whether the node is terminal, i.e. whether the game has ended at this point
	virtual bool IsTerminal() const = 0;

	// Returns true if it's the max player's turn
	virtual bool IsMaxPlayerMove() const = 0;

	// Evaluates the utility function (this can be heuristic, it's up to the implementation)
	virtual AlphaBetaScore Eval() const = 0;

	// Gets the list of all children of this node.
	virtual std::vector<ISearchNode*> GenerateChildren() = 0;

	// The action that led to this node.
	MacroSearch::Action GeneratingAction;

};

