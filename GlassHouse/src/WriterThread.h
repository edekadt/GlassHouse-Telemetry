#pragma once

#ifndef WRITERTHREAD_H
#define WRITERTHREAD_H

#define INITIAL_QUEUE_SIZE 100
#define EVENTS_LIMIT 25

#include <string>
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

class WriterThread
{
public:
	WriterThread(size_t sessionID, std::string directory);
	~WriterThread() {};
	void close();
	void enqueue(Events* m);
	void closeFile();
	void setWriteMode(WriteDestination mode_);
	void emergencyClose();

private:
	bool exit = false;
	std::thread thread;
	moodycamel::ReaderWriterQueue<Events*> eventQueue;
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