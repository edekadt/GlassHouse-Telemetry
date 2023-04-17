// GlassHouse.h - Main interface class for external use of Glasshouse Telemetry functions
// Simply boot the system at the start of your program with GlassHouse::init() and then close it at the end
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
#include <WriteDestinations.h>
#include <string>

class WriterThread;
class Events;

class GLASSHOUSE_API GlassHouse
{
public:
	// Destructor should not be called directly, it is simply public for the purposes of unique_ptr
	~GlassHouse();

	// Initializes the singleton instance
	static bool init(std::string directory = "GlassHouse-data");

	// Closes the instance and frees memory
	static bool close();
	
	// Queues an event to be serialized
	static void enqueue(Events* m);

	// Set write location of collected events (local file or server)
	void setWriteMode(WriteDestination mode_);

	// Call in case of a captured exception to close off the file with the right format
	void emergencyClose();

protected:
	GlassHouse(std::string directory);
private:
	static std::unique_ptr<GlassHouse> instance;

	WriterThread* writerThread;

	size_t sessionID;
};

#endif // GLASSHOUSE_H