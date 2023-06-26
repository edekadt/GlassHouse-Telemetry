#pragma once

#ifndef WRITERTHREAD_H
#define WRITERTHREAD_H

#define INITIAL_QUEUE_SIZE 100
#define EVENT_THREAD_TIME 10000

#include <string>
#include <thread>
#include <readerwriterqueue.h>
#include <WriteDestinations.h>

class Event;
class ISerializer;
class IPersistor;

class WriterThread
{
public:
	WriterThread(size_t sessionID, IPersistor* persistor_, ISerializer* serializer_);
	~WriterThread() {};
	void close();
	void enqueue(Event* m);
	void emergencyClose();

private:
	bool exit = false;
	std::string stringToWrite;

	IPersistor* persistor;
	ISerializer* serializer;
	size_t session_ID;

	moodycamel::ReaderWriterQueue<Event*> eventQueue;
	std::thread thread;
	void run();
};

#endif	// WRITERTHREAD_H