#pragma once

#include "Common.h"
#include "GameState.h"
#include "ISimulator.h"
#include "ISearchNode.h"
#include "AlphaBetaResult.h"
#include "Action.h"

extern int totalDecisions;
extern int totalVisitedNonTerminalNodes;

namespace MacroSearch
{

class Node :
	public ISearchNode
{
public:
	Node( GameState gameState, const ISimulator & simulator );
	~Node(void);

	virtual bool IsTerminal() const;
	virtual bool IsMaxPlayerMove() const;
	virtual AlphaBetaResult Eval() const;
	virtual std::vector<ISearchNode*> GenerateChildren();

private:
	GameState _gameState;
	const ISimulator & _simulator;

	void AddChildFromAction( Action action, std::vector<ISearchNode*> &children );
	
};

}