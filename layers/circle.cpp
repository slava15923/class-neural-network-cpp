#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
#include <ostream>
#include <iostream>
#include "voids.hpp"
class krug {
public:
	char* prefix;
	std::vector<std::vector<float>> w;
	std::vector<std::vector<float>> wNeiron;
	int ra;
	int NumNeiron;
	int NumNextLayerNeiron;
	float learning_rate;
	std::vector<float> input;
	void getfirstweight();
	std::vector<float> get();
	void corW_w(int a, int NumCorNeiron);
	void PrintW();
	void corW_wNeiron(int a, int NumCorNeiron);
};
void krug::getfirstweight() {
	w.resize(NumNeiron);
	wNeiron.resize(NumNeiron);
	for (int i = 0; i < NumNeiron; i++) {
		w[i].resize(NumNextLayerNeiron);
	}
	for (int a = 0; a < NumNeiron; a++) {
		for (int i = 0; i < NumNextLayerNeiron; i++) {
			w[a][i] = randint(-1000, 1000) / 1000;
		}
	}
	for (int i = 0; i < NumNeiron; i++) {
		wNeiron[i].resize(NumNeiron);
		for (int a = 0; a < NumNeiron; a++) {
		    if (a != i) {
				wNeiron[i][a] = randint(-1000, 1000) / 1000;
			}
		}
	}
	input.resize(NumNeiron);
}
std::vector<float> krug::get() {
	std::vector<float> ot(NumNextLayerNeiron);
	for (int i = 0; i < NumNeiron; i++) {
		for (int a = 0; a < NumNeiron; a++) {
			if (a != i) {
				input[a] = input[i] * wNeiron[i][a];
			}
		}
	}
	for (int a = 0; a < NumNextLayerNeiron; a++) {
		for (int i = 0; i < NumNeiron; i++) {
			ot[a] += ot[a] + input[i] * w[a][i];
		}
	}
	return ot;
}
void krug::corW_w(int a, int NumCorNeiron) {
	std::vector<float> b(NumNeiron);
	if (a == 1) {
		for (int i = 0; i < NumNeiron; i++) {
			w[NumCorNeiron][i] += learning_rate;
			b[i] = get()[0];
			w[NumCorNeiron][i] -= learning_rate;
		}
		float min_value = *std::min_element(b.begin(), b.end());
		w[NumCorNeiron][min_value] += learning_rate;

	}
	if (a == -1) {
		for (int i = 0; i < NumNextLayerNeiron; i++) {
			w[NumCorNeiron][i] -= learning_rate;
			b = get();
			w[NumCorNeiron][i] += learning_rate;
		}
		float min_value = *std::min_element(b.begin(), b.end());
		if (NumNeiron > 1) {
			w[NumCorNeiron][min_value] -= learning_rate;
		}
		else if (NumNeiron == 1 && NumNeiron > 0) {
			w[0][min_value] -= learning_rate;
		}
	}
}
void krug::corW_wNeiron(int a, int NumCorNeiron) {
	std::vector<float> b(NumNeiron);
	float max_value;
	float min_value;
	if (a == 1) {
		for (int i = 0; i < NumNeiron; i++) {
			wNeiron[NumCorNeiron][i] += learning_rate;
			b[i] = get()[0];
			wNeiron[NumCorNeiron][i] -= learning_rate;
		}
		max_value = *std::max_element(b.begin(), b.end());
		for (int i = 0; i < NumNeiron; i++) {
			wNeiron[NumCorNeiron][max_value] += learning_rate;
		}
	}
	if (a == -1) {
		for (int i = 0; i < NumNeiron; i++) {
			wNeiron[NumCorNeiron][i] -= learning_rate;
			b[i] = get()[0];
			wNeiron[NumCorNeiron][i] += learning_rate;
		}
		min_value = *std::min_element(b.begin(), b.end());
		for (int i = 0; i < NumNeiron; i++) {
			wNeiron[NumCorNeiron][min_value] -= learning_rate;
		}
	}
}
void krug::PrintW() {
	for (int a = 0; a < NumNeiron; a++) {
		for (int i = 0; i < NumNextLayerNeiron; i++) {
			std::cout << prefix << "w[" << a << "]" << "[" << i << "]" << " = " << w[a][i] << std::endl;
		}
	}
	for (int a = 0; a < NumNeiron; a++) {
		for (int i = 0; i < NumNeiron-1; i++) {
			if (wNeiron[a][i] != 0){
				std::cout << prefix << "wNeiron[" << a << "]" << "[" << i << "]" << " = " << wNeiron[a][i] << std::endl;
			}
		}
	}
	std::cout << std::endl;
}