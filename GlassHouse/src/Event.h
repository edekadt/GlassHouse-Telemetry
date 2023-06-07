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
#include <iostream>
#include <nlohmann/json.hpp>
#include <ctime>

enum GameEvents
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

	int time;
	GameEvents gameEvent;

	Event(GameEvents event) : gameEvent(event) {
		time = std::time(0);
	}

public:

	Event() {};

	~Event() {};

	virtual nlohmann::json serializeToJSON() const;

	GameEvents getType() const { return gameEvent; }

	void releaseEvent(const Event* event) { delete event; }
};

class SessionStart : public Event
{
public:

	SessionStart(size_t sessionID_) : Event(SESSION_START), sessionID(sessionID_)
	{
		std::cout << "START OF SESSION " << sessionID << "\n";
	}
private:
	size_t sessionID;
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

