#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "LinearNetwork.h"
#include "ActivationFunctions.h"
#include <conio.h>

LinearNetwork makeNetwork() {
	LinearNetwork net("TestingModel", 32, 16, ActivationFunctions::tanh, "tanh");

	net.addLayer(64, ActivationFunctions::relu, "relu");
	net.addLayer(64, ActivationFunctions::tanh, "tanh");
	net.addLayer(64, ActivationFunctions::relu, "relu");
	net.randomize();

	return net;
}

void evolveNets(std::vector<LinearNetwork>& networks) {
	std::sort(networks.begin(), networks.end());
	LinearNetwork best = networks.front();
	std::cout << "Generation: " << best.getEpoch() << ", Fitness: " << best.getFitness() << std::endl;
}

int main() {
	srand(time(0));
	std::vector<LinearNetwork> networks;
	for (int i = 0; i < 50; ++i) {
		networks.push_back(makeNetwork());
	}
	//net.loadEpoch(0);
	//net.setEpoch(1);

	while (true) {
		for (int i = 0; i < 5; ++i) {
			for (int i = 0; i < networks.size(); ++i) {
				networks.at(i).simulate();
			}
		}
		evolveNets(networks);

		if (_kbhit()) {
			std::cin.ignore();
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	//net.saveEpoch();
}