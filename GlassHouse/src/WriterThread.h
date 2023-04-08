#pragma once

#ifndef WRITERTHREAD_H
#define WRITERTHREAD_H
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif
#include <thread>
#include <iostream>
class CURL;
class GLASSHOUSE_API WriterThread
{
public:
	WriterThread();
protected:
	std::thread thread;
	void writeFile();
	void readFile();
	void writeServer();
	void readServer();
private:
	std::string serverUrl;
	std::string filePath;
};

#endif	// WRITERTHREAD_H