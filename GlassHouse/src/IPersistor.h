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

	size_t maxEvents = -1;		// Maximum number of events that can be enqueued before forcing a flush. Ignored if < 0;
	size_t queuedEvents = 0;	// Number of queued events
	double flushTimer = -1;		// Maximum time (in milliseconds) that can pass between writes. Ignored if < 0.
	size_t id;
	
public:
	virtual ~IPersistor() { };
	// TO DO: configurable rate of writing (by time or by number of events)
	virtual void open() {};		// Open file/connect to server/etc
	virtual void close() {};	// Close file/end server connection/etc
	bool write(Event* events);	// Returns true on successful persistence

	// Set maximum number of events that can be enqueued before forcing a flush. Ignored if < 0;
	inline void setEventLimit(size_t eventLimit) { maxEvents = eventLimit; };
	// Set maximum time (in seconds) that can pass between writes. Ignored if < 0.
	inline void setTimeLimit(double timeLimit) { flushTimer = timeLimit; };

	inline size_t getMaxEvents() { return maxEvents; };
	inline size_t getFlushTimer() { return flushTimer; };
	void setId(size_t id);
};
