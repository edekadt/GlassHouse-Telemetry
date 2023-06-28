// GlassHouse.h - Main interface class for external use of Glasshouse Telemetry functions
// Boot the system at the start of your program with GlassHouse::init() and then close it at the end
// with GlassHouse::close()
// 
#pragma once

#ifndef GLASSHOUSE_H
#define GLASSHOUSE_H

#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

#include <memory>
#include <SerializerType.h>
#include <PersistorType.h>
#include <string>

class WriterThread;
class Event;

class GLASSHOUSE_API GlassHouse
{
public:
	// Destructor should not be called directly, it is simply public for the purposes of unique_ptr
	~GlassHouse();

	// Initializes the singleton instance
	// TO DO: Error handling
	static bool init(ISerializer* ser, IPersistor* per);
	static bool init(SerializerType sType, PersistorType pType, std::string directory = "GlassHouse-data");

	// Closes the instance and frees memory
	static bool close();
	
	// Queues an event to be serialized
	static void enqueue(Event* m);

	// Call in case of a captured exception to close off the file with the right format
	static void emergencyClose();

	// TO DO: Adds an event that will be queued every s seconds for as long as the system is running. Event is stored
	// in a map under the key k and can be removed by calling removeRecurringEvent().
	// Requires specifying tickrate
	//static void addRecurringEvent();
	//static void removeRecurringEvent();

protected:
	GlassHouse(ISerializer* ser, IPersistor* per);
	ISerializer* serializer;
	IPersistor* persistor;

private:
	static std::unique_ptr<GlassHouse> instance;

	WriterThread* writerThread;

	size_t sessionID;

};

#endif // GLASSHOUSE_H