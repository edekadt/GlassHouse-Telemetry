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

class Serializable;

class GLASSHOUSE_API Event
{
protected:
	std::string id;
	std::unordered_map<std::string, Serializable*> content;

	Event(std::string event) : id(event) {
		int time = std::time(0);
		add("Time", time);
	}

public:

	Event();

	~Event();

	Event* add(std::string key, size_t val);
	Event* add(std::string key, int32_t val);
	Event* add(std::string key, double val);
	Event* add(std::string key, std::string val);
	Event* add(std::string key, bool val);

	std::string getType() const { return id; }
	const std::unordered_map<std::string, Serializable*>& getContent() const { return content; }
};

class SessionStart : public Event
{
public:
	SessionStart(size_t sessionID_);
};

class SessionEnd : public Event
{
public:
	SessionEnd(size_t sessionID_) : Event("SESSION_END")
	{
		add("SessionID", sessionID_);
	}
};

// If user does not pass a specific ID for each game, the game's number since the start of the session is used as its ID
class GameStart : public Event
{
	friend SessionStart;
	static int32_t gameCount;
public:

	GameStart(int32_t gameID_) : Event("GAME_START")
	{
		add("GameID", gameID_);
	}

	GameStart() : Event("GAME_START")
	{
		add("GameID", gameCount++);
	}
};

class GameEnd : public Event
{
	friend SessionStart;
	static int32_t gameCount;
public: 

	GameEnd(int32_t gameID_) : Event("GAME_END")
	{
		add("GameID", gameID_);
	}

	GameEnd() : Event("GAME_END")
	{
		add("GameID", gameCount++);
	}
};

class LevelStart : public Event
{
public:
	LevelStart(std::string levelID_) : Event("LEVEL_START")
	{
		add("LevelID", levelID_);
	}

	LevelStart(int32_t levelID_) : Event("LEVEL_START")
	{
		add("LevelID", levelID_);
	}
};

class LevelEnd : public Event
{
public:

	LevelEnd(std::string levelID_) : Event("LEVEL_END")
	{
		add("LevelID", levelID_);
	}

	LevelEnd(int32_t levelID_) : Event("LEVEL_END")
	{
		add("LevelID", levelID_);
	}
};
