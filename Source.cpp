#include "network.h"
#include "AI.h"


void print(){

}

int main(){

	AI ai(10, .2);

	for (int i = 0; i < 20; i++)
	{
		GameTree mainTree(10, 1);

		int winner = 0;
		int turn = 0;
		bool exit = false;

		GameNode* currentNode = new GameNode(10);
		int* sticks = new int[10];

		for (int i = 0; i < 10; i++)
		{
			if (i == 0)
				sticks[i] = 10;
			else
				sticks[i] = 0;
		}

		currentNode->setSticks(sticks);

		while (!exit){

			if (turn % 2 == 0)
			{
				std::cout << "Current Sticks: ";
				currentNode->printSticks();
				std::cout << std::endl;

				int** permutations = new int*[10];
				int* elements = new int[10];

				for (int i = 0; i < 10; i++)
					permutations[i] = new int[10];

				int max = 0;

				for (int i = 0; i < 10; i++)
				{
					if (currentNode->getSticks()[i] > max)
						max = currentNode->getSticks()[i];
				}

				int numChildren = mainTree.getValidPermutations(currentNode->getSticks(), permutations, elements, max);

				if (numChildren == 0)
				{
					winner = 1;
					std::cout << "You Lose!" << std::endl;
					exit = true;

					delete elements;
					for (int i = 0; i < 10; i++)
						delete permutations[i];

					continue;
				}

				std::cout << "Options: " << std::endl;

				for (int i = 0; i < numChildren; i++)
				{
					std::cout << i << ": ";

					for (int j = 0; j < 10; j++)
						std::cout << permutations[elements[i]][j] << " ";

					std::cout << std::endl;

				}

				int choice = 0;

				do{
					std::cout << "Option?: ";
					std::cin >> choice;
				} while (choice < 0 || choice >= numChildren);

				GameNode* newNode = new GameNode(10);
				newNode->setSticks(permutations[elements[choice]]);
				currentNode = newNode;

				ai.addToMoves(choice);
				ai.addToSticks(currentNode->getSticks());

				double* doubleSticks = new double[10];

				for (int i = 0; i < 10; i++)
				{
					doubleSticks[i] = currentNode->getSticks()[i];
				}

				//ai.getNetwork(choice)->feedForward(doubleSticks);
				ai.addToRewards(ai.getNetwork(choice)->feedForward(doubleSticks)[0]);
				ai.getNetwork(choice)->reset();

				delete elements;
				for (int i = 0; i < 10; i++)
					delete permutations[i];

				std::cout << std::endl;
			}
			else
			{
				std::cout << "Current Sticks: ";
				currentNode->printSticks();
				std::cout << std::endl;

				int numChildren = 0;

				for (int i = 0; i < 10; i++)
				{
					if (currentNode->getSticks()[i] > 2)
						numChildren = 1;
				}

				if (numChildren == 0)
				{
					winner = 2;
					std::cout << "You Win!" << std::endl;
					exit = true;
					continue;
				}

				int move = ai.getBestMove(currentNode);

				GameNode* newNode = new GameNode(10);

				newNode->setSticks(currentNode->getSticksVector()[move]->getSticks());
				std::cout << "AI chose option: ";
				newNode->printSticks();

				currentNode = newNode;

				std::cout << std::endl;
			}
			turn++;
		}

		if (winner == 1)
		{
			ai.train(100);
			ai.decreaseExploration();
		}
		else
		{
			ai.train(-100);
			ai.increaseExploration();
		}

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
	}




}