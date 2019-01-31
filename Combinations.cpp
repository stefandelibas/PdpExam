// Combinations.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

void back(vector <int> sol, int T, int n, int k) {
	if (sol.size() == k) {
		if (check(sol)) {

			mtx.lock();

			for (auto e : sol)
			{
				cout << e << " ";
			}
			cout << endl;
			mtx.unlock();
			cnt++;
		}
		return;
	}
	int last = 0;
	if (sol.size() > 0)
	{
		last = sol.back();
	}
	if (T == 1) {
		for (int i = last + 1; i <= n; ++i) {
			if (contains(sol, i)) continue;
			sol.push_back(i);
			back(sol, T, n, k);
			sol.pop_back();
		}
	}
	else {
		vector <int> x(sol);
		thread t([&]() {
			for (int i = last + 1; i <= n; i += 2) {
				if (contains(x, i)) continue;
				x.push_back(i);
				back(x, T / 2, n, k);
				x.pop_back();
			}
		});
		for (int i = last + 2; i <= n; i += 2) {
			if (contains(sol, i)) continue;
			sol.push_back(i);
			back(sol, T - T / 2, n,k);
			sol.pop_back();
		}
		t.join();
	}
}

int main() {
	back(vector <int>(), 4, 5,3);
	cout << cnt.load() << '\n';
}