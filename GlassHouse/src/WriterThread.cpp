#include <pch.h> // use stdafx.h in Visual Studio 2017 and earlier
#include <WriterThread.h>
#include <Event.h>
#include <IPersistor.h>
namespace fs = std::filesystem;


WriterThread::WriterThread(IPersistor* per)
{
    // Move to persistor and serializer

    /*if (!fs::is_directory(directory) || !fs::exists(directory)) { // Check if folder exists
        fs::create_directory(directory); // create folder
    }
    serverUrl = "http://localhost:3000/data";
    filePath = directory + "/GH_session_" + std::to_string(sessionID) + ".json";
    data = {};*/

    persistor = per;

	eventQueue = moodycamel::ReaderWriterQueue<Event*>(INITIAL_QUEUE_SIZE);
	thread = std::thread(&WriterThread::run, this);

    begin = std::chrono::steady_clock::now();
}

void WriterThread::close()
{
    exit = true;
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

	while (!exit)
	{
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin);
        // If max number of events or max time since last flush has been exceeded, flush
        if (eventQueue.size_approx() > persistor->getMaxEvents() || elapsedTime > (std::chrono::milliseconds)persistor->getFlushTimer())
            flush();
        Sleep(EVENT_THREAD_TIME);
	}
    flush();

    persistor->close();
}

void WriterThread::flush()
{
    Event* event;
    while (eventQueue.try_dequeue(event)) {
        persistor->write(event);
        delete event;
    }
    begin = std::chrono::steady_clock::now();
}

