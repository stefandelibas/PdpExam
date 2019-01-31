#include "pch.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <cassert>
#include <math.h>
#include <algorithm>    

using namespace std;

const int MAXN = 10;
const int MAXT[] = { 1, 2,4,8,10 };

int n;
int a[MAXN][MAXN], c[MAXN][MAXN];

void multLines(int x[MAXN][MAXN], int y[MAXN][MAXN],int z[MAXN][MAXN], int line, int T) {
	// mults line, line + T, line + 2 * T...
	for (int i = line; i < n; i += T) {
		for (int j = 0; j < n; ++j) {
			for (int l = 0; l < n; ++l) {
				z[i][l] += x[i][j] * y[j][l];
			}
		}
	}
}

template <class T>
void loadData(T a[MAXN][MAXN], string fileName) {
	ifstream fin(fileName);
	fin >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			fin >> a[i][j];
			cout << a[i][j] << " ";
		}
	}
}
void copyMatrix(int source[MAXN][MAXN], int dest[MAXN][MAXN])
{
	for (int i = 0; i < MAXN; i++)
	{
		for (int j = 0; j < MAXN; j++)
		{
			dest[i][j] = source[i][j];
		}
	}
}
void clearMatrix(int matrix[MAXN][MAXN])
{
	for (int i = 0; i < MAXN; i++)
	{
		for (int j = 0; j < MAXN; j++)
		{
			matrix[i][j] = 0;
		}
	}
}
void matMult(int T, bool check = false) {
	int nth = 3;
	auto start = std::chrono::high_resolution_clock::now();
	vector <thread> threads;
	loadData<int>(a, "input.in");
	cerr << "matrix of dimension " << n << '\n';

	for (int i = 0; i < min(T, n); ++i) {
		threads.push_back(thread(multLines, a, a, c, i, T));
	}
	for (int i = 0; i < min(T, n); ++i) {
		threads[i].join();
	}
	cout << "partial result:"<<endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
	
	for (int p = 3; p <= nth; p++)
	{
		vector <thread> threads;
		int d[MAXN][MAXN];
		copyMatrix(c, d);
		clearMatrix(c);
		for (int i = 0; i < min(T, n); ++i) {
			threads.push_back(thread(multLines, a, d, c, i, T));
		}
		for (int i = 0; i < min(T, n); ++i) {
			threads[i].join();
		}
		cout << "partial result:" << endl;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cout << c[i][j] << " ";
			}
			cout << endl;
		}
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
	matMult(1);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << c[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}