#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <thread>
#include <mutex>

#include "thread_sort.h"

using namespace std;

void quick_sort(vector<data_type> &a, int l, int r)
{
	int i = l, j = r;
	int mid = (l + r) / 2;
	data_type midval = (a[i] + a[j] + a[mid]) / 3;

	while (i <= j) {
		while (a[i] < midval) ++i;
		while (a[j] > midval) --j;
		if (i <= j) 
			swap(a[i++], a[j--]);
	}

	if (l < j) quick_sort(a, l, j);
	if (i < r) quick_sort(a, i, r);
}

vector<thread> Threads;

void thread_quick_sort(int depth, vector<data_type> &a, int l, int r)
{
	int i = l, j = r;
	int mid = (l + r) / 2;
	data_type midval = (a[i] + a[j] + a[mid]) / 3;

	while (i <= j) {
		while (a[i] < midval) ++i;
		while (a[j] > midval) --j;
		if (i <= j)
			swap(a[i++], a[j--]);
	}

	if (!depth) {
		if (l < j) Threads.push_back(thread(quick_sort, ref(a), l, j));
		if (i < r) Threads.push_back(thread(quick_sort, ref(a), i, r));
	}
	else {
		if (l < j) thread_quick_sort(depth + 1, a, l, j);
		if (i < r) thread_quick_sort(depth + 1, a, i, r);
	}
}

void thread_sort(int max_threads, vector<data_type> &a, int l = 0, int r = -1)
{
	Threads.clear();
	int depth = (int)log2(max_threads);
	thread_quick_sort(-depth, a, l, r);
	for (int i = 0; i < Threads.size(); i++)
		Threads[i].join();
}
