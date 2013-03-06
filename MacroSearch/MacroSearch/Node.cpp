#include "Node.h"

int totalDecisions = 0;
int totalVisitedNonTerminalNodes = 0;

Node::Node( GameState gameState, const ISimulator & simulator )
	:
	_gameState(gameState),
	_simulator(simulator)
{
}

Node::~Node(void)
{
}

bool Node::IsTerminal() const
{
	return _gameState.IsGameEnded();
}

AlphaBetaScore Node::Eval() const
{
	return _gameState.Evaluate();
}

bool Node::IsMaxPlayerMove() const
{
	return _gameState.IsMaxPlayerMove();
}

std::vector<ISearchNode*> Node::GetChildren() const
{
	std::vector<ISearchNode*> children;

	if (_gameState.GetPlayerToMove()._armyStrength > 0)
	{
		children.push_back(new Node(_simulator.GetNextState(_gameState, Attack, _gameState._isMaxPlayerMove), _simulator));
	}

	if (_gameState.GetPlayerToMove()._mineralAmount >= 50)
	{
		children.push_back(new Node(_simulator.GetNextState(_gameState, BuildProbe, _gameState._isMaxPlayerMove), _simulator));
	}

	if (_gameState.GetPlayerToMove()._mineralAmount >= 100)
	{
		children.push_back(new Node(_simulator.GetNextState(_gameState, BuildZealot, _gameState._isMaxPlayerMove), _simulator));
	}

	if (_gameState.GetPlayerToMove()._mineralAmount >= 150)
	{
		children.push_back(new Node(_simulator.GetNextState(_gameState, BuildGateway, _gameState._isMaxPlayerMove), _simulator));
	}

	children.push_back(new Node(_simulator.GetNextState(_gameState, None, _gameState._isMaxPlayerMove), _simulator));

	totalVisitedNonTerminalNodes++;
	totalDecisions += children.size();

	return children;
}
