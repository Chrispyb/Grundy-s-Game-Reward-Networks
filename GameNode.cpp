#include "GameNode.h"


//Set heapSize, alpha and beta values.
GameNode::GameNode(int heapS)
{
	heapSize = heapS;
	sticks = new int[heapSize];
}

//Add a child node to the childNodes vector.
int GameNode::addChildNode(GameNode* child){

	childNodes.push_back(child);
	return 0;
}

//Get the child indexed in vector childNodes
GameNode* GameNode::toChildNode(int elementOfNode){

	return childNodes[elementOfNode];
}

//Returns the number of child nodes.
int GameNode::getNumChildren(){
	return childNodes.size();
}

//Sets the array of sticks
void GameNode::setSticks(int* arg)
{
	for (int i = 0; i < heapSize; i++)
		sticks[i] = arg[i];
}

int* GameNode::getSticks(){
	return sticks;
}

//returns the childNode vectors of Node*s
std::vector<GameNode*> GameNode::getSticksVector(){

	return childNodes;
}

//Prints the current sticks of this node.
void GameNode::printSticks(){

	for (int i = 0; i < heapSize; i++)
		std::cout << sticks[i] << " ";

	std::cout << std::endl;
}


int GameNode::getHeapSize(){
	return heapSize;
}

GameNode::~GameNode()
{
	delete sticks;
}

//returns minmax value.
void GameNode::setReward(double val){

	reward = val;
}

double GameNode::getReward(){

	return reward;
}
