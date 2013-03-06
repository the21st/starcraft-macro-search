#pragma once

#include <vector>
#include "Common.h"

class ISearchNode
{
public:

	virtual ~ISearchNode() {}

	virtual bool IsTerminal() const = 0;
	virtual bool IsMaxPlayerMove() const = 0;
	virtual AlphaBetaScore Eval() const = 0;
	virtual std::vector<ISearchNode*> GetChildren() const = 0;

};

