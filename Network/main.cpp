#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "LinearNetwork.h"
#include "ActivationFunctions.h"

int main() {
	srand(time(0));
	//LinearNetwork net(std::vector<int>({ 32, 64, 64, 64, 8 }));
	LinearNetwork net(32, 16, 0, ActivationFunctions::tanh);
	net.addLayer(64, ActivationFunctions::relu);
	net.addLayer(64, ActivationFunctions::tanh);
	net.addLayer(64, ActivationFunctions::relu);
	net.randomize();

	while (true) {
		net.simulate();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}