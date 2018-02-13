#include "Node.h"
#include "Connection.h"

Node::Node(int type, double learningRate)
{
	this->learningRate = learningRate;
	this->bias = .1;
	this->type = type;
	zSum = 0;
}


void Node::addConnection(Connection* newConnection){
	this->connectionsToNextLayer.push_back(newConnection);
}

void Node::addToZSum(double weightedSum){
	this->zSum += weightedSum;
}

double Node:: feedForward(){
	
	if (type != 1)
		this->zSum += this->bias;

	//Assume Sigmoid for all nodes(Can be controlled with the integer type.)
	double activationValue = getSigmoid(zSum);
	this->activation = activationValue;

	for (int i = 0; i < this->connectionsToNextLayer.size(); i++)
	{
		this->connectionsToNextLayer[i]->getToNode()->addToZSum(this->connectionsToNextLayer[i]->getWeight() * activationValue);
	}

	return activationValue;
}

double Node::getSigmoid(double z){
	if (zSum >= 0)
		return zSum;
	else
		return zSum * .01;
}

double Node::deriveActivationFunction(){
	if (zSum >= 0)
		return 1;
	else
		return .01;
}

void Node::calculateDelta(){

	for (int i = 0; i < this->connectionsToNextLayer.size(); i++)
	{
		this->delta += (this->connectionsToNextLayer[i]->getWeight() * this->connectionsToNextLayer[i]->getToNode()->getDelta());
		this->connectionsToNextLayer[i]->updateWeight(activation, this->connectionsToNextLayer[i]->getToNode()->getDelta(), learningRate);
	}

	this->delta = this->delta * deriveActivationFunction();

	if (type != 1)
		this->bias -= learningRate*this->delta;
}

void Node::setDelta(double delta){
	this->delta = delta;
}

double Node::getDelta()
{
	return this->delta;
}

void Node::reset(){
	zSum = 0;
	activation = 0;
	delta = 0;
}

Node::~Node()
{
}
