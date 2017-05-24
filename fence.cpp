/*
ID: pmh1921
PROG: fence
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

int F;

vector<int> path;

void findPath(int loc, vector<int>* adjList) {
	if (adjList[loc].empty()) {
		path.push_back(loc);
	}
	else {
		while (!adjList[loc].empty()) {
			int lowest = 0;
			for (int i = 1; i < adjList[loc].size(); i++) { if (adjList[loc][i] < adjList[loc][lowest]) { lowest = i; } }
	
			int val = adjList[loc][lowest];

			adjList[loc].erase(adjList[loc].begin() + lowest);
			
			vector<int>::iterator f = find(adjList[val].begin(), adjList[val].end(), loc);
			adjList[val].erase(f);
	
			findPath(val, adjList);
		}
		path.push_back(loc);
	}
}

int main() {
    ofstream fout ("fence.out");
    ifstream fin ("fence.in");
	vector<int> adjList[501];
	vector<int> odds;
	bool isOdd[501] = {0};

	fin >> F;
	for (int i = 0; i < F; i++) {
		int a, b;
		fin >> a >> b;
		adjList[a].push_back(b);
		adjList[b].push_back(a);
	}

	for (int i = 1; i <= 500; i++) {
		int neighbours = adjList[i].size();
		if (neighbours == 0) { continue; }
		if (neighbours % 2 == 1) {
			odds.push_back(i);
			isOdd[i] = true;
		}
	}

	int lowest = 501;
	for (int i = 1; i <= 500; i++) {
		if (adjList[i].size() == 0) { continue; }

		if (odds.size() == 0 || isOdd[i]) {
			lowest = i;
			break;
		}
	}

	findPath(lowest, adjList);

	for (int i = path.size()-1; i >= 0; i--) {
		fout << path[i] << endl;
	}

    return 0;
}
