#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

#ifndef EXTEND_EVENT_DEFS
#define EXTEND_EVENT_DEFS
#endif 

#include <string>
#include <unordered_map>
#include <iostream>
#include <ctime>
#include <Serializable.h>

enum EventIdentifier
{
	SESSION_START,
	SESSION_END,
	GAME_START,
	GAME_END,
	LEVEL_START,
	LEVEL_END,
	MOUSE_CLICK EXTEND_EVENT_DEFS
};

class GLASSHOUSE_API Event
{
protected:
	EventIdentifier id;
	std::unordered_map<std::string, Serializable*> content;

	Event(EventIdentifier event) : id(event) {
		int time = std::time(0);
		add("Time", time);
	}

public:

	Event();

	~Event();

	Event add(std::string key, size_t val);
	Event add(std::string key, int32_t val);
	Event add(std::string key, double val);
	Event add(std::string key, std::string val);
	Event add(std::string key, bool val);

	EventIdentifier getType() const { return id; }
	const std::unordered_map<std::string, Serializable*>& getContent() const { return content; }

	void releaseEvent(const Event* event) { delete event; }
};

class SessionStart : public Event
{
public:

	SessionStart(size_t sessionID_) : Event(SESSION_START)
	{
		add("SessionID", sessionID_);
	}
};

class SessionEnd : public Event
{
public:

	SessionEnd(size_t sessionID_) : Event(SESSION_END), sessionID(sessionID_)
	{
		std::cout << "END OF SESSION " << sessionID << "\n";
	}
private:
	size_t sessionID;
};

class GameStart : public Event
{
public:

	GameStart() : Event(GAME_START) 
	{
		std::cout << "GAME START\n"; 
	}
};

class GameEnd : public Event
{
public: 

	GameEnd() : Event(GAME_END)
	{
		std::cout << "GAME END\n";
	}
};

class LevelStart : public Event
{
public:

	LevelStart() : Event(LEVEL_START)
	{
		std::cout << "LEVEL START\n";
	}
};

class LevelEnd : public Event
{
public:

	LevelEnd() : Event(LEVEL_END)
	{
		std::cout << "LEVEL END\n";
	}
};

class MouseClick : public Event 
{
protected:

	std::pair<int, int> mousePos;	

public:

	MouseClick() : Event(MOUSE_CLICK) 
	{
		mousePos = { 0, 0 }; 

		std::cout << "MOUSE CLICK on X " + mousePos.first;
		std::cout << " and on Y " + mousePos.second;
		std::cout << "\n"; 
	}

	void setMousePos(std::pair<int, int> pos) { mousePos = pos; }

	nlohmann::json serializeToJSON() const;
};

