#pragma once
#include <vector>
#include <cmath>


#ifndef NODE_H
#define NODE_H

class Connection;

class Node
{
public:
	Node(int, double);
	void addConnection(Connection*);
	void addToZSum(double);
	double feedForward();
	double getSigmoid(double);
	double deriveActivationFunction();
	void calculateDelta();
	void setDelta(double);
	double getDelta();
	void reset();
	~Node();

private:
	double bias;
	double zSum;
	double activation;
	double delta;
	double learningRate;
	std::vector<Connection*> connectionsToNextLayer;
	int type;

};

#endif

