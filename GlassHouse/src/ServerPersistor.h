#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

#include <IPersistor.h>
#include <string>
#include <curl/curl.h>

class GLASSHOUSE_API ServerPersistor : public IPersistor
{
protected:
	ServerPersistor(ISerializer* serializer_, std::string url_) : IPersistor(serializer_), url(url_) {};

	~ServerPersistor() {};

	virtual void persist(const std::string& s) const;
	virtual void open();
	virtual void close();

	std::string url;

	CURL* server;

	struct curl_slist* headers=NULL;
};
