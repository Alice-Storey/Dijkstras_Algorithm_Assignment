/*
 * main.cpp
 *
 *  Created on: May 23, 2013
 *      Author: alice
 */
#include <string>
#include <sstream>
#include "Graph.h"

using namespace std;

int main(int argc, char * argv [])
{
	if (argc < 3)
		return 1;

	Graph g;
	g.readFile(argv[1]);
	g.print();
	g.dijkstra(atoi(  argv[2]  )    );


	while(1)
	{
		cout << "\nTarget vertex:";
		string input;
		getline(cin, input);
		istringstream iss(input);
		int target;
		iss >> target;
		cout << "Distance = " << g.distance(target) << endl;

	}

	return 0;
}
