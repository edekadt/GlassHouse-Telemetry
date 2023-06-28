#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

#include <IPersistor.h>
#include <string>

typedef void CURL;
struct curl_slist;

class GLASSHOUSE_API ServerPersistor : public IPersistor
{
public:
	ServerPersistor(ISerializer* serializer_, std::string url_) : IPersistor(serializer_), url(url_) {};

	~ServerPersistor() {};
protected:

	virtual void persist(const std::string& s) override;
	virtual void open() override;
	virtual void close() override;

	std::string url;

	CURL* server;

	struct curl_slist* headers=NULL;
};
