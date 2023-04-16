#pragma once

#ifndef WRITERTHREAD_H
#define WRITERTHREAD_H

#define INITIAL_QUEUE_SIZE 100
#define EVENTS_LIMIT 10

#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif
#include <thread>
#include <nlohmann/json.hpp>
#include <readerwriterqueue.h>
#include <WriteDestinations.h>

/*static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}*/

class Events;

class GLASSHOUSE_API WriterThread
{
public:
	WriterThread(size_t sessionID);
	~WriterThread() {};
	void close();
	void enqueue(Events* m);
	void setWriteMode(WriteDestination mode_);

private:
	bool exit = false;
	std::thread thread;
	moodycamel::ReaderWriterQueue<Events*> eventQueue;
	nlohmann::json data;
	std::string serverUrl;
	std::string filePath;
	WriteDestination mode = WriteDestination::Local;
	int numEvents;

	void run();
	void write(nlohmann::json& data);
	void writeFile(nlohmann::json& data);
	void readFile();
	void writeServer(nlohmann::json& data, std::string sever);
	void readServer();
};

#endif	// WRITERTHREAD_H