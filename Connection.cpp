#include "Connection.h"


Connection::Connection(Node* thisNode, Node* nextLayerNode)
{

	srand(time(NULL));

	this->thisNode = thisNode;
	this->nextLayerNode = nextLayerNode;
	this->weight = (rand() % 100 + 1) / 100;
}

Node* Connection::getToNode(){
	return this->nextLayerNode;
}

double Connection::getWeight(){
	return this->weight;
}

void Connection::updateWeight(double activation, double delta, double learningRate){

	weight -= learningRate* activation*delta;
}

Connection::~Connection()
{
}
