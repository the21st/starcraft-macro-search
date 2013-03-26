#include "Node.h"
#include <algorithm>

using namespace MacroSearch;

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

std::vector<ISearchNode*> Node::GenerateChildren()
{
	std::vector<ISearchNode*> children;

	const PlayerState &playerToMove = _gameState.GetPlayerToMove();
	const std::vector<BWAPI::UnitType> &buildingsOwned = playerToMove._buildingsOwned;

	if (playerToMove._mineralAmount >= 50 && 
		playerToMove.HowManyIsProducing(BWAPI::UnitTypes::Protoss_Probe) < playerToMove.HowManyBuildingsOwned(BWAPI::UnitTypes::Protoss_Nexus))
	{
		AddChildFromAction(BuildProbe, children);
	}

	if (playerToMove._mineralAmount >= 100 && 
		playerToMove.HowManyIsProducing(BWAPI::UnitTypes::Protoss_Zealot) < playerToMove.HowManyBuildingsOwned(BWAPI::UnitTypes::Protoss_Gateway))
	{
		AddChildFromAction(BuildZealot, children);
	}

	if (playerToMove._mineralAmount >= 100 &&
		playerToMove._workerCount > 0)
	{
		AddChildFromAction(BuildPylon, children);
	}

	if (playerToMove._mineralAmount >= 150 &&
		playerToMove.HowManyBuildingsOwned(BWAPI::UnitTypes::Protoss_Pylon) > 0 &&
		playerToMove._workerCount > 0)
	{
		AddChildFromAction(BuildGateway, children);
	}

	AddChildFromAction(None, children);

	totalVisitedNonTerminalNodes++;
	totalDecisions += children.size();

	return children;
}

void Node::AddChildFromAction( Action action, std::vector<ISearchNode*> &children )
{
	Node *child = new Node(_simulator.GetNextState(_gameState, action, _gameState._isMaxPlayerMove), _simulator);
	child->GeneratingAction = action;

	child->WasMaxPlayerAction = _gameState.GetIndexOfPlayerToMove() == 0;

	children.push_back(child);
}
