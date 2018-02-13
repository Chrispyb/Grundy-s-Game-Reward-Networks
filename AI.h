#pragma once

#include "Network.h"
#include "GameNode.h"
#include "GameTree.h"

class AI
{

public:
	AI(int, double);
	int getBestMove(GameNode* currentNode);
	Network* getNetwork(int);
	void addToSticks(int*);
	void decreaseExploration();
	void increaseExploration();
	void addToMoves(int);
	void addToRewards(double);
	void train(double);
	~AI();

private:
	Network* network1;
	Network* network2;
	Network* network3;
	Network* network4;
	Network* network5;
	Network* riskNetwork;

	
	int exploreFactor = 15;
	double riskReception;
	int numRisksTaken = 0;
	double riskValue = 0;

	double discountFactor;
	std::vector<int* > sticks;
	std::vector<int> moveNumbers;
	std::vector<double> estimatedRewards;
	std::vector<double> risks;

};

