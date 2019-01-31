// BigNumbersMult.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

using namespace std;

inline vector <int> solve(vector <int> a, vector <int> b, int T) {
	vector <int> c;
	int n = a.size();
	int m = 2 * n - 1;
	c.resize(m, 0);
	vector <thread> thr;
	for (int idx = 0; idx < T; ++idx) {
		thr.push_back(thread([&, idx]() {
			for (int x = idx; x < m; x += T) {
				for (int i = 0; i < n; ++i) {
					if (x - i >= n || x - i < 0) {
						continue;
					}
					c[x] += a[i] * b[x - i];
				}
			}
		}));
	}
	for (int i = 0; i < thr.size(); ++i) {
		thr[i].join();
	}
	vector<int> result;
	int carry = 0;
	for (int i = c.size() - 1; i >= 0; i--)
	{
		c[i] += carry;
		result.push_back(c[i] % 10);
		if (c[i] > 9)
			carry = c[i] / 10;
		else
			carry = 0;
	}
	while (carry > 0)
	{
		result.push_back(carry % 10);
		carry /= 10;
	}
	reverse(result.begin(), result.end());
	return result;
}

int main() {
	ifstream fin("input.in");
	vector <int> a, b;
	int n;
	fin >> n;
	for (int i = 0; i < n; ++i) {
		int x;
		fin >> x;
		a.push_back(x);
	}
	for (int i = 0; i < n; ++i) {
		int x;
		fin >> x;
		b.push_back(x);
	}
	for (auto it : solve(a, b, 5)) {
		cout << it << ' ';
	}
	int q;
	cin >> q;
}