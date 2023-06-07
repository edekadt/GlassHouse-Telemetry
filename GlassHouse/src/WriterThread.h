#pragma once

#ifndef WRITERTHREAD_H
#define WRITERTHREAD_H

#define INITIAL_QUEUE_SIZE 100
#define EVENTS_LIMIT 25

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
	void closeFile();
	void setWriteMode(WriteDestination mode_);
	void emergencyClose();

private:
	bool exit = false;
	std::thread thread;
	moodycamel::ReaderWriterQueue<Event*> eventQueue;
	nlohmann::json data;
	std::string serverUrl;
	std::string filePath;
	WriteDestination mode = WriteDestination::Local;

	void run();
	void writeString(std::string str);
	void write(nlohmann::json& data);
	void writeFile(nlohmann::json& data);
	void readFile();
	void writeServer(nlohmann::json& data, std::string sever);
	void readServer();
};

#endif	// WRITERTHREAD_H