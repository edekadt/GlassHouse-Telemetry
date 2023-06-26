#include <pch.h> // use stdafx.h in Visual Studio 2017 and earlier
#include <WriterThread.h>
#include <Event.h>
#include <IPersistor.h>
#include <ISerializer.h>
namespace fs = std::filesystem;


WriterThread::WriterThread(size_t sessionID, IPersistor* persistor_, ISerializer* serializer_)
{
    // Move to persistor and serializer

    /*if (!fs::is_directory(directory) || !fs::exists(directory)) { // Check if folder exists
        fs::create_directory(directory); // create folder
    }
    serverUrl = "http://localhost:3000/data";
    filePath = directory + "/GH_session_" + std::to_string(sessionID) + ".json";
    data = {};*/

    session_ID = sessionID;
    persistor = persistor_;
    serializer = serializer_;

	eventQueue = moodycamel::ReaderWriterQueue<Event*>(INITIAL_QUEUE_SIZE);
	thread = std::thread(&WriterThread::run, this);
}

void WriterThread::close()
{
	thread.join();
}

void WriterThread::enqueue(Event* e)
{
	// We use emplace instead of try_emplace because try_emplace doesn't allocate additional memory if needed.
	// That would do if we didn't want to excede a fixed number of events.
	eventQueue.emplace(e);
}

void WriterThread::emergencyClose()
{
    exit = true;
}

void WriterThread::run()
{
    persistor->open();

    Event* event;

	while (!exit)
	{
        while (eventQueue.try_dequeue(event)) {
            persistor->write(event);
            delete event;
        }

        Sleep(EVENT_THREAD_TIME);
	}

    while (eventQueue.try_dequeue(event)) {
        persistor->write(event);
        delete event;
    }

    persistor->close();
}
