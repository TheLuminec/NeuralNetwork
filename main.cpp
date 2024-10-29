#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "MatrixNetwork.h"

int main() {
	srand(time(0));
	MatrixNetwork net(std::vector<int>({ 32, 64, 64, 64, 8 }));

	while (true) {
		net.simulate();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}