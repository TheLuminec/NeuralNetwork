#pragma once
#ifndef LINEARNETWORK_H
#define LINEARNETWORK_H
#include "NeuralNetwork.h"
#include "LinearLayer.h"
#include "NetworkIO.h"
#include "Evolvable.h"
#include "ActivationFunctions.h"

/**
* @brief A neural network using feed forward layers
* Standard feed forward weighted network.
*/
class LinearNetwork : public NeuralNetwork, public NetworkIO, public Evolvable {
public:
	explicit LinearNetwork(const std::string& modelName, int inputCount, int outputCount, std::function<float(float)> activation = nullptr, const std::string& activation_name = "None") :
		NeuralNetwork(inputCount, outputCount), layers(), NetworkIO(modelName, 0), Evolvable()
	{
		layers.emplace_back(Layer(inputCount, nullptr, "None"));
		layers.emplace_back(Layer(outputCount, activation, activation_name));
	}

	//Function to add a hidden layer to the end of the network
	void addLayer(int size, std::function<float(float)> activation = nullptr, const std::string& activation_name = "None") {
		if (layers.size() < 1) {
			throw std::runtime_error("Network input and output layers are not set.");
		}

		Layer outputLayer = layers.back();
		layers.pop_back();

		layers.emplace_back(size, activation, activation_name);
		layers.push_back(outputLayer);
	}

	void randomize() {
		int prevSize = 0;
		for (auto& layer : layers) {
			layer.randomWeightsAndBiases(prevSize);
			prevSize = layer.size;
		}
	}

	//Creates a deep copy of the network
	LinearNetwork* copy() const override {
		return new LinearNetwork(*this);
	}

    //Constructor to copy a LinearNetwork
    LinearNetwork(const LinearNetwork& other) :
        NeuralNetwork(other), NetworkIO(other.modelName, other.epoch), Evolvable()
    {
        layers.reserve(other.layers.size());
        for (auto& l : other.layers) {
            auto newLayer = l.copy();
            layers.push_back(newLayer);
        }
        metadata = other.metadata;
    }

    void optimize() override;

protected:
	std::vector<Layer> layers;		// layers inside the network

	void input() override;
	void output() override;
	void fitnessCalc() override;

	void forward() override {
		layers.front().values = inputs;

		Layer* prev = nullptr;
		for (auto& l : layers) {
			l.forward(prev);
			prev = &l;
		}

		outputs = layers.back().values;
        fitnessCalc();
	}

    void writeToFile(const std::string& filename) const override {
        std::ofstream outFile(filename);
        if (!outFile) {
            throw std::runtime_error("Cannot open file for writing: " + filename);
        }

        // Write model name and epoch
        outFile << modelName << std::endl;
        outFile << epoch << std::endl;

        // Write number of layers
        outFile << layers.size() << std::endl;

        // Write layers
        for (const auto& layer : layers) {
            // Write size and activation function name
            outFile << layer.size << " " << layer.activation_name << std::endl;

            // Write biases
            for (const auto& bias : layer.biases) {
                outFile << bias << " ";
            }
            outFile << std::endl;

            // Write weights
            if (!layer.weights.empty()) {
                for (const auto& weight_row : layer.weights) {
                    for (const auto& weight : weight_row) {
                        outFile << weight << " ";
                    }
                    outFile << std::endl;
                }
            }
            else {
                outFile << "NoWeights" << std::endl;
            }
        }

        // Write metadata
        outFile << metadata.size() << std::endl;
        for (const auto& kv : metadata) {
            outFile << kv.first << " " << kv.second << std::endl;
        }

        outFile.close();
    }

    void readFromFile(const std::string& filename) override {
        std::ifstream inFile(filename);
        if (!inFile) {
            throw std::runtime_error("Cannot open file for reading: " + filename);
        }

        layers.clear();

        // Read model name and epoch
        std::getline(inFile, modelName);
        inFile >> epoch;

        // Read number of layers
        size_t numLayers;
        inFile >> numLayers;

        // Read layers
        for (size_t i = 0; i < numLayers; ++i) {
            int size;
            std::string activation_name;
            inFile >> size >> activation_name;

            std::function<float(float)> activation_function = ActivationFunctions::getFunction(activation_name);
            Layer layer(size, activation_function, activation_name);

            // Read biases
            layer.biases.resize(size);
            for (int j = 0; j < size; ++j) {
                inFile >> layer.biases[j];
            }

            // Read weights
            std::string line;
            std::getline(inFile, line); // Consume the newline character
            if (i > 0) { // Input layer has no weights
                layer.weights.resize(size);
                for (int k = 0; k < size; ++k) {
                    std::getline(inFile, line);
                    if (line == "NoWeights") {
                        break;
                    }
                    std::istringstream iss(line);
                    float weight;
                    while (iss >> weight) {
                        layer.weights[k].push_back(weight);
                    }
                }
            }
            else {
                std::getline(inFile, line); // Read the "NoWeights" line
            }

            layers.push_back(layer);
            inputCount = layers.front().size;
            outputCount = layers.back().size;
            inputs.resize(inputCount);
            outputs.resize(outputCount);
        }

        // Read metadata
        size_t metadataSize;
        inFile >> metadataSize;
        for (size_t i = 0; i < metadataSize; ++i) {
            std::string key, value;
            inFile >> key >> value;
            metadata[key] = value;
        }

        inFile.close();
    }

};

#endif