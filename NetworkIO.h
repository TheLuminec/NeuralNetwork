#pragma once
#ifndef NETWORKIO_H
#define NETWORKIO_H
#include <iostream>
#include <map>
#include <vector>

class NetworkIO {
public:
	NetworkIO() : NetworkIO("", 0) {}

	explicit NetworkIO(const std::string& modelName, const int epoch) : 
		epoch(epoch), modelName(modelName), metadata()
	{}

	virtual void writeToFile(const std::string& filename) const = 0;
	virtual void readFromFile(const std::string& filename) = 0;

	virtual void saveEpoch() const = 0;
	virtual void loadEpoch(const int epoch) = 0;
	virtual std::vector<std::string> listEpochs() const = 0;

	virtual void setMetadata(const std::string& key, const std::string& meta) { metadata.emplace(key, meta); }
	virtual std::string getMetadata(const std::string& key) const { return metadata.at(key); }

protected:
	int epoch;
	std::string modelName;
	std::map<std::string, std::string> metadata;

};

#endif
