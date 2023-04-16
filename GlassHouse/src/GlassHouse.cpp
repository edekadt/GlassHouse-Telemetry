#include <pch.h> // use stdafx.h in Visual Studio 2017 and earlier
#include <GlassHouse.h>
#include <WriterThread.h>

std::unique_ptr<GlassHouse> GlassHouse::instance = nullptr;

GlassHouse::GlassHouse()
{
	writerThread = new WriterThread();
	sessionID = std::hash<size_t>{}(std::time(0));
	writerThread->enqueue(SessionStart(sessionID));
}

GlassHouse::~GlassHouse()
{
	writerThread->enqueue(SessionEnd(sessionID));
	writerThread->close();
	delete writerThread;
}

bool GlassHouse::init()
{
	instance.reset(new GlassHouse());
	return true;
}

bool GlassHouse::close()
{
	delete instance.release();
	return true;
}
