#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

#include <string>
#include <iostream>

enum GameEvents
{
	GAME_START,
	GAME_END,
	MOUSE_CLICK,
	WOUND_START,
	WOUND_END,
	SHOOT,
	HEAL,
	JUMP,
	RETURN_HOME
};

class GLASSHOUSE_API Events
{
protected:

	float time;
	GameEvents gameEvent;

public:

	Events(float timeEvent, GameEvents event) : time(timeEvent), gameEvent(event) {}

	virtual std::string serializeToJSON() const;
	virtual Events* clone() const = 0; 

	GameEvents getType() const { return gameEvent; }

	void releaseEvent(const Events* event) { delete event; }
};

class GameStart : public Events
{
public:

	GameStart(float timeEvent) : Events(timeEvent, GAME_START) 
	{
		std::cout << "GAME START\n"; 
	}

	virtual Events* clone() const; 
	virtual std::string serializeToJSON() const;
};

class GameEnd : public Events
{
public: 

	GameEnd(float timeEvent) : Events(timeEvent, GAME_END)
	{
		std::cout << "GAME END\n";
	}

	virtual Events* clone() const;
	virtual std::string serializeToJSON() const;
};

class MouseClick : public Events 
{
protected:

	std::pair<int, int> mousePos;	

public:

	MouseClick(double timeEvent) : Events(timeEvent, MOUSE_CLICK) 
	{
		mousePos = { 0, 0 }; 

		std::cout << "MOUSE CLICK on X " + mousePos.first;
		std::cout << " and on Y " + mousePos.second;
		std::cout << "\n"; 
	}

	void setMousePos(std::pair<int, int> pos) { mousePos = pos; }

	virtual Events* clone() const;
	virtual std::string serializeToJSON() const;
};

