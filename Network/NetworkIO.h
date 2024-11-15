#pragma once
#ifndef NETWORKIO_H
#define NETWORKIO_H
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>

class NetworkIO {
public:
	explicit NetworkIO(const std::string& modelName, const int epoch, const std::string& filePath = "") :
		epoch(epoch), modelName(modelName), metadata()
	{
		if (filePath == "") {
			this->filePath = modelName + "\\";
		}
		else {
			this->filePath = filePath;
		}
	}

	//Save the current epoch
	virtual void saveEpoch() {
		ensureDirectoryExists();
		std::string filename = filePath + modelName + "_epoch_" + std::to_string(epoch) + ".model";
		writeToFile(filename);
		epoch++;
	}

	//Load the given epoch if it exists
	virtual void loadEpoch(const int epoch) {
		std::string filename = filePath + modelName + "_epoch_" + std::to_string(epoch) + ".model";
		readFromFile(filename);
	}

	//List the saved epochs
	//virtual std::vector<std::string> listEpochs() const;

	//Set metadata for the file, eg parameters
	void setMetadata(const std::string& key, const std::string& meta) { metadata.emplace(key, meta); }

	//Get the metadata of the file
	std::string getMetadata(const std::string& key) const { return metadata.at(key); }

	//Sets the epoch of the network
	void setEpoch(int ep) { epoch = ep; }

	//Gets the epoch of the network
	int getEpoch() const { return epoch; }

	//Sets the file path for the network saves
	void setPath(const std::string filePath) { this->filePath = filePath; }

protected:
	int epoch;										//Current epoch
	std::string modelName;							//Name of the model
	std::map<std::string, std::string> metadata;	//networks metadata
	std::string filePath;							//Path to the file

	//Save the Network to a file
	virtual void writeToFile(const std::string& filename) const = 0;

	//Load the Network from a file
	virtual void readFromFile(const std::string& filename) = 0;

	//Called when an epoch is made to make sure the epoch folder is avaliable
	void ensureDirectoryExists() const {
		namespace fs = std::filesystem;
		fs::path dirPath(filePath);

		if (!dirPath.empty() && !fs::exists(dirPath)) {
			fs::create_directories(dirPath);
		}
	}

};

#endif
