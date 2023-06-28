#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

#include <iostream>
#include <vector>

class ISerializer;
class Event;

class GLASSHOUSE_API IPersistor
{
protected:
	ISerializer* serializer;

	IPersistor(ISerializer* serializer_): serializer(serializer_) {};

	virtual void persist(const std::string& s) = 0;
	
public:
	~IPersistor() { serializer = nullptr; };
	// TO DO: configurable rate of writing (by time or by number of events)
	virtual void open() {};		// Open file/connect to server/etc
	virtual void close() {};	// Close file/end server connection/etc
	bool write(Event* events);	// Returns true on successful persistence
};
