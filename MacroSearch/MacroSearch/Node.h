#pragma once

#include "Common.h"
#include "GameState.h"
#include "ISimulator.h"
#include "ISearchNode.h"

extern int totalDecisions;
extern int totalVisitedNonTerminalNodes;

class Node :
	public ISearchNode
{
public:
	Node( GameState gameState, const ISimulator & simulator );
	~Node(void);

	virtual bool IsTerminal() const;
	virtual bool IsMaxPlayerMove() const;
	virtual AlphaBetaScore Eval() const;
	virtual std::vector<ISearchNode*> GetChildren() const;

private:
	GameState _gameState;
	const ISimulator & _simulator;
};

