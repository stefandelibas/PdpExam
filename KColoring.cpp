// KColoring.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

using namespace std;


atomic <int> cnt(0);

void back(vector <int> sol, int T, int n, int k) {
	if (sol.size() == n) {
		cnt++;
		return;
	}
	if (T == 1) {
		for (int i = 1; i <= k; ++i) {
			sol.push_back(i);
			back(sol, T, n, k);
			sol.pop_back();			
		}
	}
	else {
		vector <int> x(sol);
		thread t([&]() {
			for (int i = 1; i <= k; i += 2) {
				x.push_back(i);
				back(x, T / 2, n,k);
				x.pop_back();
			}
		});
		for (int i = 2; i <= k; i += 2) {
			sol.push_back(i);
			back(sol, T - T / 2, n,k);
			sol.pop_back();
		}
		t.join();
	}
}

int main()
{
	back(vector<int>(),8, 8, 3);
	cout << cnt;
	int q;
	cin >> q;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
