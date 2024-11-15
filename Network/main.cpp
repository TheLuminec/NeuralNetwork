#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "LinearNetwork.h"
#include "ActivationFunctions.h"

int main() {
	srand(time(0));
	//LinearNetwork net(std::vector<int>({ 32, 64, 64, 64, 8 }));
	LinearNetwork net("TestingModel", 32, 16, ActivationFunctions::tanh, "tanh");
	
	net.addLayer(64, ActivationFunctions::relu, "relu");
	net.addLayer(64, ActivationFunctions::tanh, "tanh");
	net.addLayer(64, ActivationFunctions::relu, "relu");
	net.randomize();

	net.loadEpoch(0);
	net.setEpoch(1);
	while (true) {
		net.simulate();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}

	net.saveEpoch();
}