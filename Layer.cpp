#include "Layer.h"
#include "Connection.h"

Layer::Layer(int numNodes, int layerType)
{
	for (int i = 0; i < numNodes; i++)
	{
		Node* node = new Node(layerType, 0.001);
		this->nodes.push_back(node);
	}
}

void Layer::connectToLayer(Layer* nextLayer){

	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < nextLayer->getNodes().size(); j++)
		{
			Connection* connection = new Connection(nodes[i], nextLayer->getNodes()[j]);
			nodes[i]->addConnection(connection);
		}
	}
}

double* Layer::feedForward(){

	double* outputValues = new double[nodes.size()];

	for (int i = 0; i < nodes.size(); i++)
	{
		outputValues[i] = nodes[i]->feedForward();
	}

	return outputValues;
}

void Layer::addInputVector(double* inputVector){

	for (int i = 0; i < nodes.size(); i++)
	{
		nodes[i]->addToZSum(inputVector[i]);
	}


}
std::vector<Node*> Layer::getNodes(){

	return nodes;
}

void Layer::backPropagate(){
	for (int i = 0; i < nodes.size(); i++)
		nodes[i]->calculateDelta();
}

void Layer::reset(){
	for (int i = 0; i < nodes.size(); i++)
		nodes[i]->reset();
}

Layer::~Layer()
{
}
