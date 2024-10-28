#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "MatrixNetwork.h"

int main() {
	srand(time(0));
	MatrixNetwork net(std::vector<int>({ 6,5,5,8,5,5,6 }));

	while (true) {
		net.input();
		net.forward();
		net.output();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}