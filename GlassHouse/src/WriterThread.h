#pragma once

#ifndef WRITERTHREAD_H
#define WRITERTHREAD_H

#define INITIAL_QUEUE_SIZE 100

#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif
#include <thread>
#include <nlohmann/json.hpp>
#include <readerwriterqueue.h>

/*static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}*/
class Events;

class GLASSHOUSE_API WriterThread
{
public:
	WriterThread();
	~WriterThread();
	void writeFile(nlohmann::json data);
	void readFile();
	void writeServer(nlohmann::json data,std::string sever);
	void readServer();
	void close();
	void enqueue(Events m);
private:
	std::thread thread;
	moodycamel::ReaderWriterQueue<Events> eventQueue;

private:
	std::string serverUrl;
	std::string filePath;
	void run();
};

#endif	// WRITERTHREAD_H