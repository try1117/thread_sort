#pragma once
#include <vector>
typedef int data_type;

void quick_sort(std::vector<data_type> &a, int l, int r);
void thread_quick_sort(int depth, std::vector<data_type> &a, int l, int r);
void thread_sort(int max_threads, std::vector<data_type> &a, int l, int r);
