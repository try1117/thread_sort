#include <vector>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <cassert>

#include "thread_sort.h"

using namespace std;

const int TESTS_CNT = 10;
const int TESTS_SIZE = 1e5;
const int RANGE = 1e6;

vector<int> generate_test(int size, int range)
{
	vector<int> ans;
	while (size--)
		ans.push_back(rand() % range);
	return ans;
}

vector<long long> times_mul;
vector<vector<int>> tests;

int main()
{
	for (int i = 0; i < TESTS_CNT; ++i)
		tests.push_back(generate_test(TESTS_SIZE, RANGE));

	long long time_std, time_one;
	time_std = time_one = 0;

	for (int threads = 1; threads < (1 << 10); threads <<= 1)
	{
		time_std = time_one = 0;
		times_mul.push_back(0);

		for (int i = 0; i < TESTS_CNT; ++i)
		{
			vector<int> &cur = tests[i];
			vector<int> a(cur), b(cur), c(cur);
			clock_t t0 = clock();
			
			sort(a.begin(), a.end());
			clock_t t1 = clock();

			quick_sort(b, 0, b.size() - 1);
			clock_t t2 = clock();

			thread_sort(threads, c, 0, c.size() - 1);
			clock_t t3 = clock();

			assert(a == b && a == c);

			time_std += t1 - t0;
			time_one += t2 - t1;
			times_mul.back()+= t3 - t2;
		}
	}

	double std = (double)time_std / (CLOCKS_PER_SEC * TESTS_CNT);
	double one = (double)time_one / (CLOCKS_PER_SEC * TESTS_CNT);
	printf("std sort: %.4f\n", std);
	printf("one sort: %.4f\n", one);
	
	for (int i = 0; i < times_mul.size(); ++i) {
		double mul = (double)times_mul[i] / (CLOCKS_PER_SEC * TESTS_CNT);
		printf("mul sort: %.4f  <- %.2d threads\n", mul, 1 << i);
	}
	
	system("pause");
	return 0;
}
