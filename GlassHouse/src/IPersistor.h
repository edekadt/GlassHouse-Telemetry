#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

class ISerializer;

class GLASSHOUSE_API IPersistor
{
protected:
	ISerializer* serializer;

	IPersistor(ISerializer* serializer_): serializer(serializer_) {};
	
	~IPersistor() { serializer = nullptr; };

	virtual void persist() const = 0;

public:
	virtual bool write() const;	// returns 1 on successful persistence
};
