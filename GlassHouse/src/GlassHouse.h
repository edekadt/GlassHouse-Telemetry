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

class WriterThread;
class Events;

class GLASSHOUSE_API GlassHouse
{
public:
	GlassHouse();
	~GlassHouse();

	static bool init();
	static bool close();
	void enqueue(Events* m);
	void setWriteMode(WriteDestination mode_);

private:
	static std::unique_ptr<GlassHouse> instance;

	WriterThread* writerThread;

	size_t sessionID;
};

#endif // GLASSHOUSE_H