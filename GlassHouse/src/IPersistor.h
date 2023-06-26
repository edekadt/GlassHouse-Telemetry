#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

#include <vector>

class ISerializer;
class Event;

class GLASSHOUSE_API IPersistor
{
protected:
	ISerializer* serializer;

	IPersistor(ISerializer* serializer_): serializer(serializer_) {};
	
	~IPersistor() { serializer = nullptr; };

	virtual void persist(const std::string& s) = 0;

public:
	// TO DO: configurable rate of writing (by time or by number of events)
	virtual void begin() {};	// Write file start
	virtual void end() {};		// Write file ending
	virtual void open() {};		// Open file/connect to server/etc before flushing queue
	virtual void close() {};	// Close file/end server connection/etc after flushing queue
	bool write(Event* events);	// Returns true on successful persistence
};
