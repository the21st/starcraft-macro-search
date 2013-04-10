#pragma once

#include <iostream>
#include "BWAPI.h"
#include "AlphaBeta.h"
#include "CalendarSimulator.h"
#include "Timer.h"
#include "Node.h"
#include <assert.h>

GameState InitializeGameState();

using namespace MacroSearch;

int main(int argc, char* argv[])
{
	BWAPI::BWAPI_init();

	// create initial game state
	GameState initialGameState = InitializeGameState();

	AlphaBeta alphaBeta;

	// measure how long the search takes
	Timer timer;
	timer.start();

	// max depth to search
	int depth = 10;

	CalendarSimulator calendarSimulator;

	// the alpha-beta minimax itself
	AlphaBetaResult resultRecursive = alphaBeta.SearchRecursive(Node(initialGameState, calendarSimulator), depth, -999999, 999999);

	timer.stop();

	double time = timer.getElapsedTime();

	float averageBranchingFactor = (float)totalDecisions / (float)totalVisitedNonTerminalNodes;

	// and print the results:
	std::cout << time << " seconds" << std::endl;
	std::cout << "Score: " << resultRecursive.Score << std::endl;
	std::cout << "Action: " << resultRecursive.BestAction << std::endl;
	std::cout << "Total nodes expanded: " << totalDecisions << std::endl;

	std::cin.get();

	return 0;
}

GameState InitializeGameState()
{
	// create an initial game state:
	// a standard setup of PvP is used now (4 probes, 50 minerals and a nexus)

	GameState initialGameState;
	initialGameState._maxPlayerState._workerCount = 4;
	initialGameState._maxPlayerState._mineralAmount = 50;
	initialGameState._maxPlayerState._buildingsOwned.push_back(BWAPI::UnitTypes::Protoss_Nexus);

	//initialGameState._maxPlayerState._workerCount = 1;
	//initialGameState._maxPlayerState._mineralAmount = 500;
	//initialGameState._maxPlayerState._buildingsOwned.push_back(BWAPI::UnitTypes::Protoss_Pylon);

	initialGameState._minPlayerState._workerCount = 4;
	initialGameState._minPlayerState._mineralAmount = 50;
	initialGameState._minPlayerState._buildingsOwned.push_back(BWAPI::UnitTypes::Protoss_Nexus);

	//initialGameState._minPlayerState._mineralAmount = 200;
	//initialGameState._minPlayerState._workerCount = 2;
	//initialGameState._minPlayerState._buildingsOwned.push_back(BWAPI::UnitTypes::Protoss_Pylon);
	//initialGameState._minPlayerState._buildingsOwned.push_back(BWAPI::UnitTypes::Protoss_Gateway);

	return initialGameState;
}
