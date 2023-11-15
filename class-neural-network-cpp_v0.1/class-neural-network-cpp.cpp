#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
double ReLU(double x) {
	return (x > 0) ? x : 0;
}
double randint(int start, int end) {
	srand(time(0));
	return rand() % (end - start + 1) + start;
}
class layers {
public:
	std::vector<std::vector<double>> w;
	int ra;
	int NumNeiron;
	int NumNextLayerNeiron;
	double learning_rate;
	std::vector<double> input;
	void getfirstweight();
	std::vector<double> get();
	std::vector<double> get1input();
	void corW(int a, int NumCorNeiron);
	void PrintW();
};
void layers::getfirstweight() {
	w.resize(NumNeiron);
	for (int i = 0; i < NumNeiron; i++) {
		w[i].resize(NumNextLayerNeiron);
	}
	for (int a = 0; a < NumNeiron; a++) {
		for (int i = 0; i < NumNextLayerNeiron; i++) {
			w[a][i] = randint(-1000, 1000) / 1000;
		}
	}
	input.resize(NumNeiron);
}
std::vector<double> layers::get() {
	std::vector<double> ot(NumNextLayerNeiron);
	for (int a = 0; a < NumNeiron; a++) {
		for (int i = 0; i < NumNextLayerNeiron; i++) {
			ot[i] = input[a] * w[a][i];
		}
	}
	return ot;
}
std::vector<double> layers::get1input() {
	std::vector<double> ot(NumNextLayerNeiron);
	for (int a = 0; a < NumNeiron; a++) {
		for (int i = 0; i < NumNextLayerNeiron; i++) {
			ot[i] += input[0] * w[a][i];
		}
	}
	return ot;
}
void layers::corW(int a, int NumCorNeiron) {
	std::vector<double> b(NumNextLayerNeiron);
	std::vector<double> bb(NumNextLayerNeiron);
	double rand = randint(1, NumNeiron);
	if (a == 1) {
		for (int i = 0; i < NumNextLayerNeiron; i++) {
			w[NumCorNeiron][i] += learning_rate;
			b = get();
			w[NumCorNeiron][i] -= learning_rate;
		}
		double min_value = *std::min_element(b.begin(), b.end());
		//std::cout << min_value << std::endl;
		if (NumNeiron > 1) {
			w[NumCorNeiron][min_value] += learning_rate;
		}
		else if (NumNeiron == 1 && NumNeiron > 0) {
			w[0][min_value] += learning_rate;
		}

		for (int aa = 0; aa < NumNeiron; aa++) {
			for (int i = 0; i < NumNextLayerNeiron; i++) {
				bb[i] = 0;
			}
		}
	if (a == -1) {
		for (int i = 0; i < NumNextLayerNeiron; i++) {
			w[NumCorNeiron][i] -= learning_rate;
			bb = get();
			b[i] = bb[i];
			w[NumCorNeiron][i] += learning_rate;
		}
		double min_value = *std::min_element(b.begin(), b.end());
		if (NumNeiron > 1) {
			w[NumCorNeiron][min_value] -= learning_rate;
		}
		else if (NumNeiron == 1) {
			w[0][min_value] -= learning_rate;
		}
	}
}
}
void layers::PrintW() {
    for (int a = 0; a < NumNeiron; a++) {
        for (int i = 0; i < NumNextLayerNeiron; i++) {
            std::cout << "w[" << a << "]" << "[" << i << "]" << " = " << w[a][i] << std::endl;
        }
    }
    std::cout << std::endl;
}
