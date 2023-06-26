#include <pch.h> // use stdafx.h in Visual Studio 2017 and earlier
#include <GlassHouse.h>
#include <WriterThread.h>
#include <Event.h>

std::unique_ptr<GlassHouse> GlassHouse::instance = nullptr;

GlassHouse::GlassHouse(std::string directory)
{
	sessionID = std::hash<size_t>{}(std::time(0));
	writerThread = new WriterThread(sessionID, directory);
	writerThread->enqueue(new SessionStart(sessionID));
}

GlassHouse::~GlassHouse()
{
	writerThread->enqueue(new SessionEnd(sessionID));
	writerThread->close();
	delete writerThread;
}

bool GlassHouse::init(std::string directory)
{
	instance.reset(new GlassHouse(directory));
	return true;
}

bool GlassHouse::close()
{
	delete instance.release();
	return true;
}

void GlassHouse::enqueue(Event* m)
{
	instance.get()->writerThread->enqueue(m);
}

void GlassHouse::emergencyClose()
{
	instance.get()->writerThread->emergencyClose();
}
