#pragma once
#include <stdio.h>   
#include <stdlib.h>
#include <time.h> 

#ifndef CONNECTION_H
#define CONNECTION_H

class Node;

class Connection
{
public:
	Connection(Node*, Node*);
	Node* getToNode();
	double getWeight();
	void updateWeight(double, double, double);
	~Connection();

private:
	Node* nextLayerNode;
	Node* thisNode;
	double weight;
};

#endif
