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
#include <nlohmann/json.hpp>
class GLASSHOUSE_API WriterThread
{
public:
	WriterThread();
	void writeFile(nlohmann::json data);
	void readFile();
	void writeServer(nlohmann::json data,std::string sever);
	void readServer();
protected:
	std::thread thread;

private:
	std::string serverUrl;
	std::string filePath;
};

#endif	// WRITERTHREAD_H