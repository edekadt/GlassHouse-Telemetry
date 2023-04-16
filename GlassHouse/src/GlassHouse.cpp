#include <pch.h> // use stdafx.h in Visual Studio 2017 and earlier
#include <GlassHouse.h>
#include <WriterThread.h>
#include <Events.h>

std::unique_ptr<GlassHouse> GlassHouse::instance = nullptr;

GlassHouse::GlassHouse()
{
	sessionID = std::hash<size_t>{}(std::time(0));
	writerThread = new WriterThread(sessionID);
	writerThread->enqueue(new SessionStart(sessionID));
}

GlassHouse::~GlassHouse()
{
	writerThread->enqueue(new SessionEnd(sessionID));
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

void GlassHouse::enqueue(Events* m)
{
	instance.get()->writerThread->enqueue(m);
}

void GlassHouse::setWriteMode(WriteDestination mode_)
{
	writerThread->setWriteMode(mode_);
}
