/*
ID: pmh1921
PROG: stamps
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream fout ("stamps.out");
    ifstream fin ("stamps.in");
	int K, N;
	fin >> N >> K;

	int biggestStamp = 0;
	int* stampVals = new int[K];

	for (int i = 0; i < K; i++) {
		int a;
		fin >> a;
		stampVals[i] = a;
		if (a > biggestStamp) { biggestStamp = a; }
	}

	int** dp1, **dp2;
	dp1 = new int*[biggestStamp + 1];
	dp2 = new int*[biggestStamp + 1];

	for (int i = 0; i <= biggestStamp; i++) {
		dp1[i] = new int[2];
		dp2[i] = new int[2];
		dp1[i][0] = dp2[i][0] = dp1[i][1] = dp2[i][1] = 0;
	}

	dp1[0][0] = 1;
	dp1[0][1] = 0;

	for (int i = 0; i < K; i++) {
		int sv = stampVals[i];
		for (int j = 0; j + sv <= biggestStamp; j++) {
			int* o = dp1[j];
			if (o[0] && o[1] < N) {
				int* ju = dp1[j + sv];

				if (!ju[0] || o[1] + 1 < ju[1]) {
					ju[1] = o[1] + 1;
					ju[0] = true;
				}
			}
		}
	}

	for (int i = 1; i <= biggestStamp; i++) {
		if (!dp1[i][0]) {
			fout << (i-1) << endl;
			exit(0);
		}
	}

	int times = 1;
	while (1) {
		for (int i = 0; i < K; i++) {
			int sv = stampVals[i];
			for (int j = -sv; j + sv <= biggestStamp; j++) {
				
				int* o;
				if (j < 0) { o = dp1[biggestStamp + 1 + j]; }
				else {		 o = dp2[j]; }
	
	
				if (o[0] && o[1] < N) {
					int* ju = dp2[j + sv];
	
					if (!ju[0] || o[1] + 1 < ju[1]) {
						ju[1] = o[1] + 1;
						ju[0] = true;
					}
				}
			}
		}
	
		
		for (int i = 0; i <= biggestStamp; i++) {
			if (!dp2[i][0]) {
				fout << (times*(biggestStamp+1) + i-1) << endl;
				exit(0);
			}
		}


		int** t = dp1;
		dp1 = dp2;
		dp2 = t;
		for (int i = 0; i <= biggestStamp; i++) { dp2[i][0] = dp2[i][1] = 0; }

		times++;
	}

    return 0;
}
