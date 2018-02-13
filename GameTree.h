#pragma once
#include "GameNode.h"

class AI;
class GameTree
{
public:
	GameTree(int, int);
	int create(GameNode*, int, AI* ai, int);
	void setMaxDepth(int);
	int getValidPermutations(int*, int**, int*, int);
	int compareArrays(int*, int*);
	GameNode* getRoot();
	GameNode* getCurrent();
	GameNode* changeToIndexOfCurrent(int);
	double evaluate(GameNode*, int, AI* ai);
	~GameTree();

private:
	int heapSize;
	GameNode* root;
	GameNode* currentNode;
	GameNode* previousNode;
	int numNodes = 0;
	int maxPly;
	int maxDepth;

};

