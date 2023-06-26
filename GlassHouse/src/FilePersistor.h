#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

#include <IPersistor.h>
#include <string>

class GLASSHOUSE_API FilePersistor : public IPersistor
{
protected:
	FilePersistor(ISerializer* serializer_, std::string directory_): IPersistor(serializer_), directory(directory_) {};
	
	~FilePersistor() {};

	virtual void persist(const std::string& s) const;
	virtual void open();
	virtual void close();

	std::string directory;
};
