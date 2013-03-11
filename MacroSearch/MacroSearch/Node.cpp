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
	CleanUpChildren();
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

std::vector<ISearchNode*> Node::GenerateChildren()
{
	CleanUpChildren();

	if (_gameState.GetPlayerToMove()._armyStrength > 0)
	{
		_children.push_back(new Node(_simulator.GetNextState(_gameState, Attack, _gameState._isMaxPlayerMove), _simulator));
	}

	if (_gameState.GetPlayerToMove()._mineralAmount >= 50)
	{
		_children.push_back(new Node(_simulator.GetNextState(_gameState, BuildProbe, _gameState._isMaxPlayerMove), _simulator));
	}

	if (_gameState.GetPlayerToMove()._mineralAmount >= 100)
	{
		_children.push_back(new Node(_simulator.GetNextState(_gameState, BuildZealot, _gameState._isMaxPlayerMove), _simulator));
	}

	if (_gameState.GetPlayerToMove()._mineralAmount >= 150)
	{
		_children.push_back(new Node(_simulator.GetNextState(_gameState, BuildGateway, _gameState._isMaxPlayerMove), _simulator));
	}

	_children.push_back(new Node(_simulator.GetNextState(_gameState, None, _gameState._isMaxPlayerMove), _simulator));

	totalVisitedNonTerminalNodes++;
	totalDecisions += _children.size();

	return _children;
}

void Node::CleanUpChildren()
{
	for (size_t i = 0; i < _children.size(); i++)
	{
		delete _children[i];
	}
	_children.clear();
}
