#pragma once

#ifndef WRITERTHREAD_H
#define WRITERTHREAD_H

#define INITIAL_QUEUE_SIZE 100
#define EVENT_THREAD_TIME 10000

#include <string>
#include <thread>
#include <readerwriterqueue.h>

class Event;
class IPersistor;

class WriterThread
{
public:
	WriterThread(IPersistor* per);
	~WriterThread() {};
	void close();
	void enqueue(Event* m);
	void emergencyClose();

private:
	bool exit = false;

	IPersistor* persistor = nullptr;

	moodycamel::ReaderWriterQueue<Event*> eventQueue;
	std::thread thread;
	void run();
};

#endif	// WRITERTHREAD_H