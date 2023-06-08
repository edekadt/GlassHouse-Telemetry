#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

#include <IPersistor.h>
#include <string>

class GLASSHOUSE_API ServerPersistor : public IPersistor
{
protected:
	ServerPersistor(ISerializer* serializer_, std::string url_) : IPersistor(serializer_), url(url_) {};

	~ServerPersistor() {};

	virtual void persist(const std::string& s) const;

	std::string url;
};
