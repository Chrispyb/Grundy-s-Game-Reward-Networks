#pragma once
#include "Layer.h"
#include <iostream>
#include <time.h> 

#ifndef NETWORK_H
#define NETWORK_H

class Network
{
public:
	Network(int*, int);
	double* feedForward(double*);
	double* evaluateCost(double*, double*, int);
	double* deriveCost(double*, double*, int);
	void backPropagate(double*, double*);
	void backPropagateRegression();
	void addToRegressionCosts(double*, double*);
	void reset();

	~Network();
private:
	std::vector<Layer*> layers;
	int numIterations;
	double* regressionCosts;
};

#endif

