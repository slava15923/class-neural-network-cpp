#pragma once
#include <ctime>
#include <algorithm>
float ReLU(float x) {
	return (x > 0) ? x : 0;
}
float randint(int start, int end) {
	srand(time(0));
	return rand() % (end - start + 1) + start;
}
