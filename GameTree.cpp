#include "GameTree.h"
#include "AI.h"

//Set heapSize and ply for the tree.
GameTree::GameTree(int numInHeap, int ply)
{
	heapSize = numInHeap;
	maxPly = ply;
}


//Recursively generate tree, calculation min-max and alpha-beta values along the way.
int GameTree::create(GameNode* parentNode, int depth, AI* ai, int numNodes){

	if (depth == maxDepth)
		return 0;

	//If there is no root of the tree, add one, and call create() wit numNodes == 1
	if (numNodes == 0)
	{
		GameNode* rootNode;

		rootNode = parentNode;
		root = rootNode;
		numNodes++;
		//root->printSticks();
		//depth++;
		create(rootNode, depth, ai, numNodes);

	}
	else
	{

		//Get the possible permutations from the parent Node's stick array.
		int** permutations = new int*[heapSize];

		for (int i = 0; i < heapSize; i++)
			permutations[i] = new int[heapSize];

		int* elements = new int[heapSize];

		for (int i = 0; i < heapSize; i++)
			elements[i] = -1;

		int max = 0;

		for (int i = 0; i < heapSize; i++)
		{
			if (parentNode->getSticks()[i] > max)
				max = parentNode->getSticks()[i];
		}

		int numPermutations = getValidPermutations(parentNode->getSticks(), permutations, elements, max);

		for (int i = 0; i < numPermutations; i++)
		{
			GameNode* newNode = new GameNode(heapSize);
			numNodes++;

			newNode->setSticks(permutations[elements[i]]);

			create(newNode, depth + 1, ai, numNodes);

			parentNode->addChildNode(newNode);

			evaluate(newNode, i, ai);
		}

		if (depth == maxDepth - 1)
			return 0;

		for (int i = 0; i < heapSize; i++)
			delete permutations[i];

		delete elements;
	}

	return 0;
}

//Get valid permutations for the tree.
int GameTree::getValidPermutations(int* input, int** permutations, int* elements, int max){

	int numPermutations = 0;


	for (int i = 0; i < max; i++)
	{

		for (int j = 0; j < heapSize; j++)
			permutations[i][j] = input[j];

	}


	if (max % 2 == 0)
		max--;
	else
		max = max;

	for (int i = 1; i <= max / 2; i++)
	{
		int stayInLoop = 0;

		for (int j = 0; j < heapSize && stayInLoop == 0; j++)
		{
			if (input[j] == 1 || input[j] == 2)
			{
				//permutations[i][j] = input[j];
				continue;
			}
			else
			{
				int A = input[j] - i;
				int B = i;

				if (A != B && A > 0 && B > 0 && !(A == 1 && B == 1))
				{
					for (int k = 0; k < heapSize && stayInLoop == 0; k++)
					{
						if (input[k] == 0)
						{
							permutations[i][j] = A;
							permutations[i][k] = B;
							//std::cout << A << " " << B << std::endl;
							stayInLoop = 1;
							elements[numPermutations] = i;
							numPermutations++;
						}
						else
						{
							//permutations[i][k] = input[k];
							//permutations[i][j] = input[j];
						}

					}
				}
			}
		}
	}

	return numPermutations;
}

//Get root
GameNode* GameTree::getRoot(){
	return root;
}

//Set max depth of the tree.
void GameTree::setMaxDepth(int depth){
	maxDepth = depth;
}

GameNode* GameTree::getCurrent(){
	return currentNode;
}

GameNode* GameTree::changeToIndexOfCurrent(int index){
	currentNode = currentNode->getSticksVector()[index];

	return currentNode;
}

int GameTree::compareArrays(int* A, int* B){


	for (int i = 0; i < 7; i++)
	{
		if (A[i] != B[i])
			return 0;
	}

	return 1;
}

//Evaluation function. Evaluates a -1 or 1 for nodes that aren't absolute leaf nodes, 2/-2 for winning or losing nodes.
double GameTree::evaluate(GameNode* childNode, int type, AI* ai){

	int value = 0;

	double sticksForNetwork[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int* sticks = childNode->getSticks();

	for (int i = 0; i < 10; i++)
		sticksForNetwork[i] = (double)sticks[i];

	Network* network = ai->getNetwork(type);

	childNode->setReward(network->feedForward(sticksForNetwork)[0]);
	network->reset();

	return 1;
}

GameTree::~GameTree()
{
}
