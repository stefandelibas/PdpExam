// NQueens.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>

using namespace std;

mutex mtx;
bool check(vector <int> v) {

	for (int i = 0; i < v.size(); i++)
	{
		for (int j = i + 1; j < v.size(); j++)
		{
			int deltaRow = abs(i - j);
			int deltaCol = abs(v[i] - v[j]);
			if (deltaRow == deltaCol)
			{
				return false;
			}
		}
	}
	return true;
}

bool contains(vector <int> v, int n) {
	for (auto it : v) {
		if (it == n) {
			return true;
		}
	}
	return false;
}

atomic <int> cnt;


void back(vector <int> sol, int T, int n) {
	if (sol.size() == n) {
		if (check(sol)) {
			mtx.lock();
			for (int i = 0;i < sol.size(); i++)
			{
				cout << "row=" << i+1 << " col=" << sol[i] << endl;
			}
			cout << endl;
			mtx.unlock();
		}
		return;
	}
	if (T == 1) {
		for (int i = 1; i <= n; ++i) {
			if (contains(sol, i)) continue;
			sol.push_back(i);
			back(sol, T, n);
			sol.pop_back();
		}
	}
	else {
		vector <int> x(sol);
		thread t([&]() {
			for (int i = 1; i <= n; i += 2) {
				if (contains(x, i)) continue;
				x.push_back(i);
				back(x, T / 2, n);
				x.pop_back();
			}
		});
		for (int i = 2; i <= n; i += 2) {
			if (contains(sol, i)) continue;
			sol.push_back(i);
			back(sol, T - T / 2, n);
			sol.pop_back();
		}
		t.join();
	}
}

int main() {
	back(vector <int>(), 2, 4);
	cout << "algo ended";
	int q;
	cin >> q;
}