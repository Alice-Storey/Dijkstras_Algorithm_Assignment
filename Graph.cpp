/*
 * Graph.cpp
 *
 *  Created on: May 23, 2013
 *      Author: alice
 */

#include "Graph.h"
#include <sstream>
#include <fstream>
#include <math.h>

Graph::Graph()
{

}

Graph::~Graph()
{
	// TODO Auto-generated destructor stub
}


void Graph::readFile(string filename)
{
	ifstream infile(filename.c_str() );
	string line;

	getline(infile, line);
	int numNodes = atoi(line.c_str());


	for ( int i=0; i<numNodes; i++)
	{
		getline(infile, line);
		istringstream iline(line);

		int nodenum;
		iline >> nodenum;
		Node node(nodenum);

		nodenum = -2;
		while ( nodenum != -1  )
		{
			double weight;
			iline >> nodenum;
			if (nodenum != -1)
			{
				iline >> weight;
				node.edges.push_back(Edge(nodenum, weight));
			}

		}

		nodes.insert(node);
	}
}

void Graph::print()
{
	cout << nodes.findMin().id << " " << nodes.findMin().dist <<  endl;
}

void Graph::dijkstra(int src)
{
	nodes.decreaseKey(src,0);

	while (!nodes.isEmpty())
	{

		Node u = nodes.findMin();
		nodes.deleteMin();

		if (u.dist==INFINITY)
			break;


		for (list<Edge>::iterator it=u.edges.begin(); it != u.edges.end(); it++)
		{
			Node *v = & nodeat( (*it).node );
			double altdist = u.dist + (*it).weight;

			if (altdist < (*v).dist)
			{
				cout << altdist << "<" << (*v).dist << endl;
				(*v).prev = u.id;
				nodes.decreaseKey( (*v).id, altdist);
			}
		}

	}

}

double Graph::distance (int target)
{
	cout << "prev " << nodeat(target).prev << endl;
	return nodeat(target).dist;
}
