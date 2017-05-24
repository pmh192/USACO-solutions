/* ID: pmh1921
PROG: cowtour
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

double** adjMat;
vector<int>* adjList;
int**nodes;

int* categories;

double max(double a, double b) {
	return a > b ? a : b;
}

double min(double a, double b) {
	return a < b ? a : b;
}

void dfsFill(int node, int value) {
	if (categories[node] == value) { return; }
	categories[node] = value;

	vector<int> adj = adjList[node];
	for (int i = 0; i < adj.size(); i++) {
		dfsFill(adj[i], value);
	}
}

int floodFill(int N) {
	categories = new int[N];
	for (int i = 0; i < N; i++) {
		categories[i] = -1;
	}

	int count = 0;
	for (int i = 0; i < N; i++) {
		if (categories[i] != -1) { continue; }

		dfsFill(i, count);
		count++;
	}

	return count;
}


int main() {
    ofstream fout ("cowtour.out");
    ifstream fin ("cowtour.in");
	int N;
	fin >> N;

	adjMat = new double*[N];
	for (int i = 0; i < N; i++) { adjMat[i] = new double[N]; }

	adjList = new vector<int>[N];
	nodes = new int*[N];
 

	for (int i = 0; i < N; i++) {
		nodes[i] = new int[2];
		fin >> nodes[i][0] >> nodes[i][1];
	}

	string mat;
	
	for (int i = 0; i < N; i++) {
		fin >> mat;

		for (int j = 0; j < N; j++) {
			if (j < i) { continue; }

			if (mat[j] == '1') {
				double dist = sqrt((nodes[i][0] - nodes[j][0])*(nodes[i][0] - nodes[j][0]) + (nodes[i][1] - nodes[j][1])*(nodes[i][1] - nodes[j][1]));
				adjMat[i][j] = adjMat[j][i] = dist;
				adjList[i].push_back(j);
				adjList[j].push_back(i);
			}
			else {
				adjMat[i][j] = adjMat[j][i] = -1;
			}
		}
	}

	int categoryCount = floodFill(N);

	double** dist = new double*[N];
	for (int i = 0; i < N; i++) {
		dist[i] = new double[N];
		for (int n = 0; n < N; n++) {
			dist[i][n] = adjMat[i][n];
		}
	}

	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (dist[i][k] > 0 && dist[j][k] > 0) {
					if (dist[i][j] < 0 || dist[i][k] + dist[j][k] < dist[i][j]) {
						dist[i][j] = dist[i][k] + dist[j][k];
					}
				}
			}
		}
	}

	double* maxDist = new double[N];
	for (int i = 0; i < N; i++) {
		double m = 0;
		for (int j = 0; j < N; j++) {
			if (i == j || dist[i][j] < 0) { continue; }

			m = max(dist[i][j], m);
		}
		maxDist[i] = m;
	}

	double* diameters = new double[categoryCount];
	for (int i = 0; i < categoryCount; i++) {
		double m = 0;
		for (int j = 0; j < N; j++) {
			if (categories[j] == i) {
				m = max(maxDist[j], m);
			}
		}
		diameters[i] = m;
	}


	double diameter = numeric_limits<double>::max();

	for (int i = 0; i < N; i++) {
		for (int j = i+1; j < N; j++) {
			if (categories[i] == categories[j]) { continue; }

			double dist = sqrt((nodes[i][0] - nodes[j][0])*(nodes[i][0] - nodes[j][0]) + (nodes[i][1] - nodes[j][1])*(nodes[i][1] - nodes[j][1]));
			double newDiameter = maxDist[i] + maxDist[j] + dist;

			double biggestDiameter = max(diameters[categories[i]], diameters[categories[j]]);
			newDiameter = max(newDiameter, biggestDiameter);

			diameter = min(diameter,  newDiameter);
		}
	}

	fout << std::fixed << std::setprecision(6) << diameter << endl;

    return 0;
}
