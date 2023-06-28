#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

#include <IPersistor.h>
#include <string>
#include <fstream>
#include <iostream>

class GLASSHOUSE_API FilePersistor : public IPersistor
{
public:
	FilePersistor(ISerializer* serializer_, std::string directory_) : IPersistor(serializer_), directory(directory_) {};

	~FilePersistor() {};
	
	void setId(size_t id_) { id = id_; };
protected:
	virtual void persist(const std::string& s) override;
	virtual void open() override;
	virtual void close() override;

	std::string directory;
	mutable std::ofstream output_file;
	size_t id;
};
