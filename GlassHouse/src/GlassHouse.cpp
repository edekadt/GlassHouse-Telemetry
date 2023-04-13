#include <pch.h> // use stdafx.h in Visual Studio 2017 and earlier
#include <GlassHouse.h>
#include <WriterThread.h>

GlassHouse::GlassHouse()
{

	writerThread = new WriterThread();
}

GlassHouse::~GlassHouse()
{
	writerThread->close();
	delete writerThread;
}
