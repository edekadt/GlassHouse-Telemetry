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
	LEVEL_END EXTEND_EVENT_DEFS
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
	SessionEnd(size_t sessionID_) : Event(SESSION_END)
	{
		add("SessionID", sessionID_);
	}
};

class GameStart : public Event
{
public:

	GameStart(int32_t gameID_) : Event(GAME_START) 
	{
		add("GameID", gameID_);
	}
};

class GameEnd : public Event
{
public: 

	GameEnd(int32_t gameID_) : Event(GAME_END)
	{
		add("GameID", gameID_);
	}
};

class LevelStart : public Event
{
public:

	LevelStart(int32_t levelID_) : Event(LEVEL_START)
	{
		add("LevelID", levelID_);
	}
};

class LevelEnd : public Event
{
public:

	LevelEnd(int32_t levelID_) : Event(LEVEL_END)
	{
		add("LevelID", levelID_);
	}
};