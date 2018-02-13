#include "AI.h"


AI::AI(int heapSize, double discount)
{
	int how[5] = { 10, 5, 5, 2, 1 };

	network1 = new Network(how, 5);
	network2 = new Network(how, 5);
	network3 = new Network(how, 5);
	network4 = new Network(how, 5);
	network5 = new Network(how, 5);
	riskNetwork = new Network(how, 5);
	riskReception = .8;
	discountFactor = discount;
}

Network* AI::getNetwork(int index){

	if (index == 0)
		return network1;
	else if (index == 1)
		return network2;
	else if (index == 2)
		return network3;
	else if (index == 3)
		return network4;
	else if (index == 4)
		return network5;
}

int AI::getBestMove(GameNode* currentNode){
	GameTree tree(10, 1);

	tree.setMaxDepth(2);
	tree.create(currentNode, 0, this, 0);

	srand(time(NULL));

	int selection = rand() % 100;
	int whichElement = 0;

	
	double* sticksVec = new double[10];

	for (int i = 0; i < 10; i++)
		sticksVec[i] = currentNode->getSticks()[i];

	riskValue += riskNetwork->feedForward(sticksVec)[0];
	risks.push_back(riskValue);
	std::cout << "Risk Value: " << riskValue << std::endl;

	if (currentNode->getNumChildren() > 0)
	{
		if (selection >= riskValue)
		{
			double outerMax = INT_MIN;
			int outerElement = 0;

			for (int i = 0; i < currentNode->getNumChildren(); i++)
			{
				GameNode* newNode = currentNode->getSticksVector()[i];

				double max = INT_MIN;
				int element = 0;

				for (int j = 0; j < newNode->getNumChildren(); j++)
				{
					if (newNode->getSticksVector()[j]->getReward() > max)
					{
						max = newNode->getSticksVector()[j]->getReward();
					}
				}

				if (currentNode->getSticksVector()[i]->getReward() + discountFactor*max > outerMax)
				{
					outerMax = currentNode->getSticksVector()[i]->getReward() + discountFactor*max;
					outerElement = i;
				}

				std::cout << "Reward: " << currentNode->getSticksVector()[i]->getReward() + discountFactor*max << std::endl;
			}

			sticks.push_back(currentNode->getSticksVector()[outerElement]->getSticks());
			moveNumbers.push_back(outerElement);
			estimatedRewards.push_back(currentNode->getSticksVector()[outerElement]->getReward());
			whichElement = outerElement;
		}
		else
		{
			numRisksTaken++;

			int theSelection = rand() % currentNode->getNumChildren();

			sticks.push_back(currentNode->getSticksVector()[theSelection]->getSticks());
			moveNumbers.push_back(theSelection);
			estimatedRewards.push_back(currentNode->getSticksVector()[theSelection]->getReward());

			whichElement = theSelection;
		}
	}

	riskNetwork->reset();
	return whichElement;
}

void AI::train(double reward){

	reward = reward / sticks.size();

	double avgRisk = riskValue / numRisksTaken;

	for (int i = 0; i < sticks.size(); i++)
	{
		double inputVec[10];

		for (int j = 0; j < 10; j++)
			inputVec[j] = sticks[i][j];

		Network* network = getNetwork(moveNumbers[i]);

		double rewards[1] = { 0 };
		rewards[0] = reward;
	
		
		double actual = estimatedRewards[i];
		double actualVal[1];
		actualVal[0] = actual;

	
		network->backPropagate(actualVal, rewards);
	}

	for (int i = 0; i < risks.size(); i++)
	{
		double inputVec[10];

		for (int j = 0; j < 10; j++)
			inputVec[j] = sticks[i][j];


		if (reward == 100 && numRisksTaken == 0)
		{
			double* riskArg = new double[1];
			double* newRisk = new double[1];

			riskArg[0] = risks[i];
			newRisk[0] = risks[i] + riskReception/20;

			riskNetwork->backPropagate(riskArg, newRisk);

			delete riskArg;
			delete newRisk;
		}
		else if (reward == 100 && numRisksTaken > 0)
		{
			double* riskArg = new double[1];
			double* newRisk = new double[1];

			riskArg[0] = risks[i];
			newRisk[0] = risks[i] + numRisksTaken*riskReception;

			riskNetwork->backPropagate(riskArg, newRisk);

			delete riskArg;
			delete newRisk;
		}
		else if (reward == 0 && numRisksTaken == 0)
		{
		double* riskArg = new double[1];
		double* newRisk = new double[1];

		riskArg[0] = risks[i];
		newRisk[0] = risks[i] - riskReception;

		riskNetwork->backPropagate(riskArg, newRisk);

		delete riskArg;
		delete newRisk;
		}
		else if (reward == 0 && numRisksTaken > 0)
		{
			double* riskArg = new double[1];
			double* newRisk = new double[1];

			riskArg[0] = risks[i];
			newRisk[0] = risks[i] - numRisksTaken * 1 / riskReception;

			riskNetwork->backPropagate(riskArg, newRisk);

			delete riskArg;
			delete newRisk;
		}
	}
	moveNumbers.clear();
	sticks.clear();
	estimatedRewards.clear();
	risks.clear();
}

void AI::addToSticks(int* stick){
	sticks.push_back(stick);
}

void AI::addToMoves(int move){
	moveNumbers.push_back(move);
}

void AI::addToRewards(double reward){
	estimatedRewards.push_back(reward);
}

void AI::decreaseExploration(){
	exploreFactor--;
}

void AI::increaseExploration(){
	exploreFactor++;
}

AI::~AI()
{
}
