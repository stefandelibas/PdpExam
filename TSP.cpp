// HamiltonPath.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <map>
#include<mutex>

using namespace std;

const int maxn = 1005;
mutex mtx;
int n, m;

bool solved = false;
vector <int> sol;
vector <int> g[maxn];
map<pair<int, int>, int> costs;
int minCost = INT_MAX;

inline void back(vector <int> nodes, int T, int cost) {
	if (nodes.size() == n) {
		vector <int> adj = g[nodes.back()];
		
		if (find(adj.begin(), adj.end(), nodes[0]) != adj.end())
		{
			cost += costs[pair<int, int>(nodes[0], nodes[nodes.size() - 1])];
			if (cost < minCost)
			{
				solved = true;
				sol = nodes;
				minCost = cost;
			}
			/*{
				mtx.lock();
				cout << "cost:" << minCost << "\n";
				for (auto it : sol) {
					cout << it << ' ';
				}
				cout << "\n";
				mtx.unlock();
			}*/		
		}
		return;
	}
	if (T > 1) {
		vector <int> adj = g[nodes.back()];
		thread t([adj, nodes, T, cost]() {
			for (int i = 0; i < adj.size(); i += 2) {
				if (find(nodes.begin(), nodes.end(), adj[i]) == nodes.end()) {
					vector <int> aux(nodes);
					int c = costs[pair<int, int>(nodes.back(), adj[i])];
					aux.push_back(adj[i]);
					back(aux, T / 2, cost+c);
				}
			}
		});
		for (int i = 1; i < adj.size(); i += 2) {
			if (find(nodes.begin(), nodes.end(), adj[i]) == nodes.end()) {
				vector <int> aux(nodes);
				int c = costs[pair<int, int>(nodes.back(), adj[i])];
				aux.push_back(adj[i]);
				back(aux, T - T / 2, cost+c);
			}
		}
		t.join();
	}
	else {
		for (auto it : g[nodes.back()]) {
			if (find(nodes.begin(), nodes.end(), it) == nodes.end()) {
				vector <int> aux(nodes);

				int c = costs[pair<int, int>(it, nodes.back())];
				aux.push_back(it);
				back(aux, T, cost+c);
			}
		}
	}
}

int main() {
	ifstream fin("input.in");
	fin >> n >> m;

	for (int i = 0; i < m; ++i) {
		int x, y,cost;
		fin >> x >> y >> cost;
		g[x].push_back(y);
		g[y].push_back(x);
		costs[pair<int, int>(x, y)] = cost;
		costs[pair<int, int>(y,x)] = cost;
	}
	//for (int i = 0; i < m; i++)
	//{
	//	vector<int> c = g[i];
	//	for (int j = 0; j < c.size(); j++)
	//		cout << i << "->" << c[j] << " cost:" << costs[pair<int,int>(i,c[j])]<< "\n";
	//	cout << endl;
	//}
	vector <int> init;
	init.push_back(0);
	back(init, 4,0);
	if (!solved) {
		cout << "Not found!\n";
	}
	else {
		cout << "min cost:" << minCost<<"\n";
		for (auto it : sol) {
			cout << it << ' ';
		}
	}
}