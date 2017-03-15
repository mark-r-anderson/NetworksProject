#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Network;
class Router;

// network object that contains all routers
class Network {
public:
	Network(string); // instantiates the network object and all routers
	void findShortestPath(int, int); // finds the minimum cost path between two routers
	Router* minCandidate(); // returns the router in the candidates vector with the smallest pathLength
	void reset(); // reset all routers within the network
	vector<Router*> routers; // vector that stores all routers within the network
	vector<Router*> candidates; // vector of the candidate routers used in Dijkstra's algorithm
	vector<Router*> reached; // vector of all the reached routers used in Dijkstra's algorithm
	Router* currentRouter; // the current router used during Dijkstra's algorithm
};

// router object that holds all of the router information
class Router {
public:
	Router(); // instantiates router object
	int routerNumber; // the router's number
	int pathLength; // the total cost to get to this router during Dijkstra's algorithm
	int outgoingCost; // the cost from going from the current router to its neighbour
	vector<Router*> neighbours; // vector that holds the current router's neighbouring routers
	Router* predecessor; // the router before the current router when finding the shortest path
};