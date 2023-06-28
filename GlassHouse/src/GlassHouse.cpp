#include <pch.h> // use stdafx.h in Visual Studio 2017 and earlier
#include <GlassHouse.h>
#include <WriterThread.h>
#include <Event.h>

std::unique_ptr<GlassHouse> GlassHouse::instance = nullptr;

GlassHouse::GlassHouse(ISerializer* ser, IPersistor* per)
{
	sessionID = std::hash<size_t>{}(std::time(0));
	serializer = ser;
	persistor = per;
	FilePersistor* fper = dynamic_cast<FilePersistor*>(per);
	if (fper) {
		fper->setId(sessionID);
	}
	writerThread = new WriterThread(per);
	writerThread->enqueue(new SessionStart(sessionID));
}

GlassHouse::~GlassHouse()
{
	writerThread->enqueue(new SessionEnd(sessionID));
	writerThread->close();
	delete serializer;
	delete persistor;
	delete writerThread;
}

bool GlassHouse::init(ISerializer* ser, IPersistor* per) {
	instance.reset(new GlassHouse(ser, per));
	return true;
}

bool GlassHouse::init(SerializerType sType, PersistorType pType, std::string directory) {
	ISerializer* ser = nullptr;
	switch (sType){
	case SerializerType::Json:
		ser = new JsonSerializer();
		break;
	default:
		return false;
	}

	IPersistor* per = nullptr;
	switch (pType) {
	case PersistorType::Local:
		per = new FilePersistor(ser, directory);
		break;
	case PersistorType::Server:
		per = new ServerPersistor(ser, directory);
		break;
	default:
		return false;
	}

	instance.reset(new GlassHouse(ser, per));
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
