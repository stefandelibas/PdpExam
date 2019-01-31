// MatrixMul.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <cassert>
#include <math.h>
#include <algorithm>    

using namespace std;

const int MAXN = 2005;
const int MAXT[] = { 1, 2,4,8,10 };

int n, m, k;
int a[MAXN][MAXN], b[MAXN][MAXN], c[MAXN][MAXN];

void multLines(int line, int T) {
	// mults line, line + T, line + 2 * T...
	for (int i = line; i < n; i += T) {
		for (int j = 0; j < m; ++j) {
			for (int l = 0; l < k; ++l) {
				c[i][l] += a[i][j] * b[j][l];
			}
		}
	}
}

template <class T>
void loadData(T a[MAXN][MAXN], T b[MAXN][MAXN], string fileName) {
	ifstream fin(fileName);
	fin >> n >> m >> k;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			fin >> a[i][j];
		}
	}
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < k; ++j) {
			fin >> b[i][j];

		}
	}
}

void matMult(int T, bool check = false) {
	auto start = std::chrono::high_resolution_clock::now();
	vector <thread> threads;
	loadData<int>(a, b, "mult5.in");
	cerr << "matrix of dimension " << n << '\n';

	for (int i = 0; i < min(T, n); ++i) {
		threads.push_back(thread(multLines, i, T));
	}
	for (int i = 0; i < min(T, n); ++i) {
		threads[i].join();
	}
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	cerr << "Elapsed time: " << elapsed.count() << '\n';
}

void statistics() {
	for (int i = 0; i < 7; ++i) {
		int t = MAXT[i];
		cout << t << " threads\n";
		matMult(t);
	}
}

int main() {
	matMult(8);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
	
	return 0;
}