/*
ID: pmh1921
PROG: contact
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct myString {
	string s;

	bool operator<(const myString& o) const {
		if (s.size() < o.s.size()) { return true; }
		if (o.s.size() < s.size()) { return false; }

		return s < o.s;
	}
};

vector<string> strRep(vector<pair<int, int> > ints, int A) {
	//sort(ints.begin(), ints.end());

	vector<string> r;
	vector<myString> toSort;
	for (int i = 0; i < ints.size(); i++) {
		pair<int, int> item = ints[i];

		int size = item.first;
		int n = item.second;
		string s;

		while (n > 0) {
			char c = '0' + (n%2);
			s = c + s;
			n /= 2;
		}
	
		while (s.size() < size) { s = "0" + s; }	
		myString ms;
		ms.s = s;
		toSort.push_back(ms);
	}

	sort(toSort.begin(), toSort.end());

	for (int i = 0; i < toSort.size(); i++) {
		r.push_back(toSort[i].s);
	}

	return r;
}


int main() {
    ofstream fout ("contact.out");
    ifstream fin ("contact.in");
	int A, B, N;
	fin >> A >> B >> N;

	int** hashes = new int*[B+1];
	for (int i = A; i <= B; i++) {
	   	hashes[i] = new int[i];
		for (int n = 0; n < i; n++) { hashes[i][n] = 0; }
	}

	int* pows2 = new int[14];
	pows2[0] = 1;
	for (int i = 1; i < 14; i++) {
		pows2[i] = 2*pows2[i-1];
	}

	int** repeats = new int*[B+1];
	for (int i = A; i <= B; i++) {
	   	repeats[i] = new int[pows2[i+1]];
		for (int n = 0; n < pows2[i+1]; n++) { repeats[i][n] = 0; }
   	}

	int count = 0;
	char c;
	while (fin >> c) {
		if (c != '0' && c != '1') { continue; }

		for (int n = A; n <= B; n++) {
			int pos = (n-1) - (count % n);

			for (int o = 0; o < n; o++) {
				if (count < o) { continue; }

				int offPos = (pos + o) % n;
					
				if (c == '1') {
					hashes[n][o] += pows2[offPos];
				}

				if (offPos == 0) {
					repeats[n][hashes[n][o]]++;
					hashes[n][o] = 0;
				}
			}
		}

		count++;
	}

	priority_queue<int> mostFreq;
	unordered_map< int, vector<pair<int, int> > > freqList;
	for (int n = A; n <= B; n++) {
		for (int i = 0; i < pows2[n+1]; i++) {
			int repeated = repeats[n][i];

			if (repeated > 0) {
				pair<int, int> item;
			   	item.first = n; item.second = i;
				mostFreq.push(repeated);
				freqList[repeated].push_back(item);
			}
		}
	}

	int lastAmount = -1;
	for (int i = 0; i < N && !mostFreq.empty(); i++) {
		int amount = mostFreq.top();
		mostFreq.pop();

		if (amount == lastAmount) {
			i--;
			continue;
		}
		lastAmount = amount;

		vector<string> strs = strRep(freqList[amount], A);

		fout << amount << endl;
		for (int i = 0; i < strs.size(); i++) {
			fout << strs[i];
			if (i != strs.size() - 1) { // if not the last one
				if ((i+1) % 6 == 0) {
					fout << endl;
				}
				else {
					fout << " ";
				}
		   	}
		}

		fout << endl;
	}


    return 0;
}
