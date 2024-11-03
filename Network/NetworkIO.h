#pragma once
#ifndef NETWORKIO_H
#define NETWORKIO_H
#include <iostream>
#include <map>
#include <vector>

class NetworkIO {
public:
	explicit NetworkIO(const std::string& modelName, const int epoch) : 
		epoch(epoch), modelName(modelName), metadata()
	{}

	//Save the Network to a file
	virtual void writeToFile(const std::string& filename) const = 0;

	//Load the Network from a file
	virtual void readFromFile(const std::string& filename) = 0;

	//Save the current epoch
	virtual void saveEpoch() const = 0;

	//Load the given epoch if it exists
	virtual void loadEpoch(const int epoch) = 0;

	//List the saved epochs
	virtual std::vector<std::string> listEpochs() const = 0;

	//Set metadata for the file, eg parameters
	virtual void setMetadata(const std::string& key, const std::string& meta) { metadata.emplace(key, meta); }

	//Get the metadata of the file
	virtual std::string getMetadata(const std::string& key) const { return metadata.at(key); }

protected:
	int epoch;										//Current epoch
	std::string modelName;							//Name of the model
	std::map<std::string, std::string> metadata;	//networks metadata

};

#endif
