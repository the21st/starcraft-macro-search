#pragma once

#include "Common.h"
#include "GameState.h"
#include "ISimulator.h"

extern int totalDecisions;
extern int totalVisitedNonTerminalNodes;

class Node
{
public:
	Node( GameState gameState, const ISimulator & simulator );
	~Node(void);

	bool IsTerminal();
	bool IsMaxPlayerMove();
	AlphaBetaScore Eval();
	std::vector<Node> GetChildren();

private:
	GameState _gameState;
	const ISimulator & _simulator;
};

