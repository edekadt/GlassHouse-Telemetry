#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

class GLASSHOUSE_API IPersistor
{
protected:
	IPersistor() {};
	
	~IPersistor() {};

public:
	virtual bool write() = 0;	// returns 1 on successful persistence
};
