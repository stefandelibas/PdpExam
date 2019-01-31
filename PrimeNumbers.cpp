// PrimeNumbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <thread>
#include <numeric>
#include <mutex>  


const int NR_THREADS = 16;

using namespace std;

std::mutex mtx;           // mutex for critical section

void getPrimesLinearly(vector<int> & primes, int n)
{
	for (int x = 2; x <= n; x++)
	{
		bool isPrime = true;
		for (int y = 2; y < x / 2; y++)
		{
			if (x % y == 0)
			{
				isPrime = false;
				break;
			}
		}
		if (isPrime)
		{
			primes.push_back(x);
		}
	}
}

void crossInvalidNumebrs(int x, vector<int> & primes, int n)
{
	int y = x+x;
	while (y <= n)
	{
		mtx.lock();

		auto it = std::find(primes.begin(), primes.end(), y);
		if (it != primes.end())
		{
			//int index = std::distance(primes.begin(), it);
			//cout << "erase" << primes[index] << endl;
			primes.erase(it);
		}

		mtx.unlock();
		y+=x;
	}
}

void getPrimesThreads(vector<int> & primes, int n)
{
	primes.resize(n-1);
	std::iota(std::begin(primes), std::end(primes), 2);
	int sqN = sqrt(n);	
	cout << sqN << endl;
	vector<int> firstPrimes;
	getPrimesLinearly(firstPrimes, sqN);

	//cout << "sqrt(n)=" << sqN<<endl << "prime numbers till sqrt(n):" << endl;
	/*for (int i = 0; i < firstPrimes.size(); i++)
	{
		cout << firstPrimes[i] << " " ;
	}
	cout << endl;*/
	thread threads[8];
	int i;
	for (i = 0; i < firstPrimes.size() && i < NR_THREADS; i++)
	{
		threads[i] = thread([&]() {
			crossInvalidNumebrs(firstPrimes[i],primes,n);
		});
	}
	while (i < firstPrimes.size())
	{
		crossInvalidNumebrs(firstPrimes[i], primes, n);
		i++;
	}

	for (i = 0; i < firstPrimes.size() && i < NR_THREADS; i++)
	{
		threads[i].join();
	}	
}


int main()
{
    std::cout << "Hello World!\n"; 
	vector<int> iulia;
	vector<int> primes;
	/////////////////////////////////////////////////////////////
	clock_t begin = clock();
	getPrimesThreads(iulia, 100000);
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "time elapsed on threads:" << elapsed_secs << "\n";
	/*for (int i = 0; i < iulia.size(); i++)
	{
		cout << iulia[i] << " ";
	}*/
	/////////////////////////////////////////////////////////////
	begin = clock();
	getPrimesLinearly(primes, 100000);
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "time elapsed linerly:" << elapsed_secs << "\n";
	/////////////////////////////////////////////////////////////
	/*for (int i = 0; i < iulia.size(); i++)
	{
		cout << primes[i] << " ";
	}*/

	int q;
	cin >> q;
	return 0;
}
