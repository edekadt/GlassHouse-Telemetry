#include <pch.h> // use stdafx.h in Visual Studio 2017 and earlier
#include <GlassHouse.h>
#include <WriterThread.h>

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
