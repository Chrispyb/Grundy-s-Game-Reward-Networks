#pragma once
#pragma once
#include <vector>
#include <iostream>

class GameNode
{
public:
	GameNode(int);
	int addChildNode(GameNode*);
	GameNode* toChildNode(int);
	int* getSticks();
	void setSticks(int*);
	void printSticks();
	int getNumChildren();
	int getHeapSize();
	void setReward(double);
	double getReward();
	std::vector<GameNode*> getSticksVector();
	~GameNode();

private:
	int heapSize;
	std::vector<GameNode*> childNodes;
	int* sticks;
	double reward;

};
