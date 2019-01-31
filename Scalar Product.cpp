// NrPermutations.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

using namespace std;

void scoalar_mult(vector <int>& sol,vector<int> & a, vector<int> & b, int T,int left, int right) {
	if (T == 1)
	{
		for (int i = left; i <= right; i++)
		{
			sol[i] = a[i] * b[i];
		}
	}
	else {
		int s = right - left + 1;
		s /= 2;
		thread t([&]() {
			scoalar_mult(sol, a, b, T / 2, left + s, right);
		});
		scoalar_mult(sol, a, b, T - T / 2, 0, left + s - 1);
		t.join();
	}
}

int main() {
	vector<int>sol;	
	sol.resize(8);
	vector<int>a{1,2,3,1,2,3,4,5};
	vector<int>b{2,2,2,2,2,2,2,2};

	scoalar_mult(sol, a, b, 1, 0, 7);

	for (int i = 0; i < 8; i++)
	{
		cout << sol[i] << " ";
	}
	int q;
	cin >> q;
}