/*
ID: pmh1921
PROG: agrinet
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream fout ("agrinet.out");
    ifstream fin ("agrinet.in");
	int N;
	fin >> N;

	int** adjMat = new int*[N];
	for (int i = 0; i < N; i++) {
		adjMat[i] = new int[N];
		for (int j = 0; j < N; j++) {
			fin >> adjMat[i][j];
		}
	}


	int* distance = new int[N];
	for (int i = 0; i < N; i++) { distance[i] = -1; }

	distance[0] = 0;
	int visited = 1;

	int totalDistance = 0;

	while (visited < N) {
		int closestNode, closestDistance = 1<<30, from;

		for (int i = 0; i < N; i++) {
			if (distance[i] != -1) { // visited
				for (int j = 0; j < N; j++) {
					if (i == j) { continue; }

					if (adjMat[i][j] < closestDistance && distance[j] == -1) { //unvisited
						from = i;
						closestNode = j;
						closestDistance = adjMat[i][j];
					}
				}
			}
		}

		distance[closestNode] = distance[from] + closestDistance;
		totalDistance += closestDistance;
		visited++;
	}

	fout << totalDistance << endl;
    return 0;
}
