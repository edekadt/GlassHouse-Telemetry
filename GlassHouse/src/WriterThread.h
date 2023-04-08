#pragma once

#ifndef WRITERTHREAD_H
#define WRITERTHREAD_H

#include <thread>

class Event;

class WriterThread
{
public:
	WriterThread();
protected:
	std::thread thread;

	void writeFile();
};

#endif	// WRITERTHREAD_H