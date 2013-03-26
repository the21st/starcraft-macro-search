#pragma once

#include <iostream>
#include "BWAPI.h"
#include "AlphaBeta.h"
#include "CalendarSimulator.h"
#include "Timer.h"
#include "Node.h"
#include <assert.h>

using namespace MacroSearch;

int main(int argc, char* argv[])
{
	BWAPI::BWAPI_init();

	GameState initialGameState;
	initialGameState._minPlayerState._workerCount = 3;
	initialGameState._minPlayerState._buildingsOwned.push_back(BWAPI::UnitTypes::Protoss_Nexus);
	initialGameState._maxPlayerState._workerCount = 4;
	initialGameState._maxPlayerState._buildingsOwned.push_back(BWAPI::UnitTypes::Protoss_Nexus);

	AlphaBeta alphaBeta;

	Timer timer;
	timer.start();

	int depth = 3;

	CalendarSimulator calendarSimulator;
	//ISearchNode * initialNode = new Node(initialGameState, calendarSimulator);
	//AlphaBetaResult resultIterative = alphaBeta.SearchIterative(initialNode, depth, -999999, 999999);
	//delete initialNode;

	AlphaBetaResult resultRecursive = alphaBeta.SearchRecursive(Node(initialGameState, calendarSimulator), depth, -999999, 999999);

	//assert(resultIterative.Score == resultRecursive.Score);

	timer.stop();

	double time = timer.getElapsedTime();

	float averageBranchingFactor = (float)totalDecisions / (float)totalVisitedNonTerminalNodes;

	std::cout << time << " seconds" << std::endl;
	std::cout << "Score: " << resultRecursive.Score << std::endl;
	std::cout << "Total nodes expanded: " << totalDecisions << std::endl;

	std::cin.get();

	return 0;
}