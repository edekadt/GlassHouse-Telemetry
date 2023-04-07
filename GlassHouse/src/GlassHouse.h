// GlassHouse.h - Main interface class for external use of Glasshouse Telemetry functions
// Simply instantiate the class at the start of your program with GlassHouse::init() and then close it at the end
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

class WriterThread;

class GLASSHOUSE_API GlassHouse
{
public:
	GlassHouse();

private:

};

#endif // GLASSHOUSE_H