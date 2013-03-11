#pragma once

#include <iostream>
#include "BWAPI.h"
#include "AlphaBeta.h"
#include "CalendarSimulator.h"
#include "Timer.h"
#include "Node.h"

int main(int argc, char* argv[])
{
	//BWAPI::BWAPI_init();

	GameState initialGameState;
	initialGameState._minPlayerState._workerCount = 4;
	initialGameState._minPlayerState._buildingsOwned.push_back(Nexus);
	initialGameState._maxPlayerState._workerCount = 3;
	initialGameState._maxPlayerState._buildingsOwned.push_back(Nexus);

	auto alphaBeta = AlphaBeta();

	Timer timer;
	timer.start();

	AlphaBetaScore result = alphaBeta.SearchUsingRecursion(Node(initialGameState, CalendarSimulator()), 10, -999999, 999999);

	timer.stop();

	auto time = timer.getElapsedTime();

	float averageBranchingFactor = (float)totalDecisions / (float)totalVisitedNonTerminalNodes;

	std::cout << time << " seconds" << std::endl;
	std::cout << "Score: " << result << std::endl;
	std::cout << "Total nodes expanded: " << totalDecisions << std::endl;

	std::cin.get();

	return 0;
}