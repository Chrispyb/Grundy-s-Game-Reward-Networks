#include "Network.h"


Network::Network(int* layerSizes, int numLayers)
{
	for (int i = 0; i < numLayers; i++)
	{
		Layer* layer;

		if (i == 0)
			layer = new Layer(layerSizes[i], 1);
		else
			layer = new Layer(layerSizes[i], 0);

		this->layers.push_back(layer);
	}

	for (int i = 0; i < layers.size() - 1; i++)
	{
		layers[i]->connectToLayer(layers[i + 1]);
	}

	int outputSize = layers[layers.size() - 1]->getNodes().size();
	regressionCosts = new double[outputSize];

	for (int i = 0; i < outputSize; i++)
		regressionCosts[i] = 0;

	numIterations = 0;
}

double* Network::feedForward(double* inputVector){

	double* outputValues = new double[layers[layers.size() - 1]->getNodes().size()];

	layers[0]->addInputVector(inputVector);

	for (int i = 0; i < layers.size(); i++)
	{
		if (i == layers.size() - 1)
		{
			outputValues = layers[i]->feedForward();
		}
		else
		{
			layers[i]->feedForward();
		}
	}

	return outputValues;

}

double* Network::evaluateCost(double* outputVector, double* targetVector, int sizeOfVectors)
{
	double* cost = new double[sizeOfVectors];

	for (int i = 0; i < sizeOfVectors; i++)
		cost[i] = 1/2* pow(targetVector[i] - outputVector[i], 2);

	return cost;
}

double* Network::deriveCost(double* outputVector, double* targetVector, int sizeOfVectors){

	double* costDerivative = new double[sizeOfVectors];

	for (int i = 0; i < sizeOfVectors; i++)
		costDerivative[i] = outputVector[i] - targetVector[i];

	return costDerivative;
}

void Network::backPropagate(double* outputVector, double* targetVector){

	int outputSize = layers[layers.size() - 1]->getNodes().size();

	double* costDerivatives = deriveCost(outputVector, targetVector, outputSize);


	for (int i = 0; i < outputSize; i++)
	{
		layers[layers.size() - 1]->getNodes()[i]->setDelta(costDerivatives[i] * layers[layers.size() - 1]->getNodes()[i]->deriveActivationFunction());
	}

	for (int i = layers.size() - 1; i >= 0; i--)
		layers[i]->backPropagate();

	reset();
}


void Network::backPropagateRegression(){

	int outputSize = layers[layers.size() - 1]->getNodes().size();

	double* costDerivatives = new double[5];

	for (int i = 0; i < outputSize; i++)
		costDerivatives[i] = 2*(regressionCosts[i] / numIterations);

	for (int i = 0; i < outputSize; i++)
		layers[layers.size() - 1]->getNodes()[i]->setDelta(costDerivatives[i] * layers[layers.size() - 1]->getNodes()[i]->deriveActivationFunction());

	for (int i = layers.size() - 2; i >= 0; i--)
		layers[i]->backPropagate();

	reset();
}

void Network::addToRegressionCosts(double* outputVector, double* targetVector){

	int outputSize = layers[layers.size() - 1]->getNodes().size();

	double* costDerivatives = deriveCost(outputVector, targetVector, outputSize);

	for (int i = 0; i < outputSize; i++)
		regressionCosts[i] += costDerivatives[i];

	numIterations++;
}

void Network::reset(){

	for (int i = layers.size() - 1; i >= 0; i--)
		layers[i]->reset();
}

Network::~Network()
{
}
