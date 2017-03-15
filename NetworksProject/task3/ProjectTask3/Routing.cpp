#include "Routing.h"

using namespace std;

int main() {
	Network n = Network("network_routers.txt"); // create network object using text file
	n.findShortestPath(1,15); // find the shortest path

	system("pause");
}

Network::Network(string filename) {
	string line;
	ifstream file(filename);
	if (file.is_open())
	{
		// create and add routers into "routers" vector
		while (getline(file, line)) {
			Router* r = new Router();
			routers.push_back(r);
		}

		// go back to first line in the file
		file.clear();
		file.seekg(0, ios::beg);

		// continue reading file until end of file
		while (getline(file, line)) {
			// read and save value before the ",", which is the router number
			int routerNum = stoi(line.substr(0, line.find(",")));
			// read and save value after the "," and before the ":", which is the router's cost
			int cost = stoi(line.substr(line.find(",")+1, line.find(":")-line.find(",")-1));
			string s = line.substr(line.find(":\t")+2);

			vector<Router*> neighbours;
			int prevIndex = 0;
			int nextIndex = s.find("\t");
			// continue finding index of next tab until end of line
			while (nextIndex != string::npos) {
				// read and save value between the two tab indexes, which is a neighbouring router
				neighbours.push_back(routers[stoi(s.substr(prevIndex, nextIndex)) - 1]);
				prevIndex = nextIndex + 1;
				nextIndex = s.find("\t", prevIndex);
			}
			neighbours.push_back(routers[stoi(s.substr(prevIndex)) - 1]);

			// save router information into router object
			routers[routerNum - 1]->routerNumber = routerNum;
			routers[routerNum - 1]->outgoingCost = cost;
			routers[routerNum - 1]->neighbours = neighbours;
		}
		file.close();
	}
	else {
		cout << "Unable to open file" << endl;
	}
}

// finds path with minimum cost between two routers
void Network::findShortestPath(int source, int destination) {
	// resets all router variables
	reset();

	// set source router path length to 0 and add to candidates vector
	routers[source-1]->pathLength = 0;
	candidates.push_back(routers[source-1]);

	// continue until there are no more routers in candidates vector
	while (!candidates.empty()) {
		// find the candidate router with the minimum path length
		currentRouter = minCandidate();

		// stop and print results if destination router is reached
		if (currentRouter->routerNumber == destination) {
			int cost = currentRouter->pathLength;
			string route = to_string(currentRouter->routerNumber);

			while (currentRouter->predecessor != NULL) {
				currentRouter = currentRouter->predecessor;
				route = to_string(currentRouter->routerNumber) + "-" + route;
			}

			cout << "The optimal route from the source router to the destination router is " << route << " with a total cost of " << cost << "." << endl;
			return;
		}

		// interate through all of the current router's neighbours
		for (Router* neighbour: currentRouter->neighbours) {
			// calculate the cost to the current neighbour
			int costToNeighbour = currentRouter->pathLength + currentRouter->outgoingCost;
			// if calculated cost is less than neighbour's existing cost
			if (costToNeighbour < neighbour->pathLength) {
				// add neighbour to candidates vector if it has not been seen yet
				if (neighbour->pathLength == INT_MAX)
					candidates.push_back(neighbour);
				// update neighbour information
				neighbour->pathLength = costToNeighbour;
				neighbour->predecessor = currentRouter;
			}
		}
		reached.push_back(currentRouter);
	}

	// if no optimal route exists
	cout << "A route from the source routre to the destination router does not exist." << endl;
	return;
}

// returns candidate with smallest path length
Router* Network::minCandidate() {
	int minIndex;
	int minPathLength = INT_MAX;
	// iterate through all the candidates and find router with the smallest path length
	for (int i = 0; i < candidates.size(); i++) {
		if (candidates.at(i)->pathLength < minPathLength) {
			minIndex = i;
			minPathLength = candidates.at(i)->pathLength;
		}
	}
	// remove and return router with smallest path length
	Router* r = candidates.at(minIndex);
	candidates.erase(candidates.begin() + minIndex);
	return r;
}

// resets all variables
void Network::reset() {
	for (Router* router : routers) {
		router->pathLength = INT_MAX;
		router->predecessor = NULL;
	}
	candidates.clear();
	reached.clear();
	currentRouter = NULL;
}

Router::Router() {
	pathLength = INT_MAX;
	predecessor = NULL;
}