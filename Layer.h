#pragma once
#include "Node.h"

#ifndef LAYER_H
#define LAYER_H

class Layer
{
public:
	Layer(int, int);
	void connectToLayer(Layer*);
	std::vector<Node*> getNodes();
	double* feedForward();
	void addInputVector(double*);
	void backPropagate();
	void Layer::reset();
	~Layer();
private:
	std::vector<Node*> nodes;
};

#endif

