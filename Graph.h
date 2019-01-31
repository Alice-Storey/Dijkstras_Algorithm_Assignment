/*
 * Graph.h
 *
 *  Created on: May 23, 2013
 *      Author: alice
 */
#include <list>
#include <string>
#include <math.h>
#include "BinaryHeap.h"
using namespace std;

#ifndef GRAPH_H_
#define GRAPH_H_



struct Edge
{
	int node;
	double weight;

	Edge( int n=-1, double w=-1 )
	  : node(n), weight(w) { }
};

class Node
{
public:
	int id;
	list<Edge> edges;
	double dist;
	bool visited;
	int prev;

	Node( int i=-1, double d=INFINITY  ) : id( i ), dist( d ), prev(-1), visited (false) { }

	bool operator< (Node &b)
	{
		return dist < b.dist;
	}
	bool operator> (Node &b)
	{
		return dist > b.dist;
	}
	bool operator== (Node &b)
	{
		return dist == b.dist;
	}
	bool operator<= (Node &b)
	{
		return dist <= b.dist;
	}
	bool operator>= (Node &b)
	{
		return dist >= b.dist;
	}

};


class Graph
{
public:
	Graph();
	virtual ~Graph();
	void readFile(string filename);
	void print();
	Node& getNode(int key);
	void dijkstra(int src);
	double distance(int target);

private:
	BinaryHeap< Node  > nodes;
	Node& nodeat (int id) {return nodes.itemat(id);}

};

#endif /* GRAPH_H_ */
