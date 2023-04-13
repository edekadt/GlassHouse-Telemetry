#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

enum GameEvents
{
	SESSION_START,
	SESSION_END,
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

	Events(GameEvents event) : gameEvent(event) {
		
	}

public:

	Events(){}

	nlohmann::json serializeToJSON() const;

	GameEvents getType() const { return gameEvent; }

	void releaseEvent(const Events* event) { delete event; }
};

class GameStart : public Events
{
public:

	GameStart() : Events(GAME_START) 
	{
		std::cout << "GAME START\n"; 
	}
};

class GameEnd : public Events
{
public: 

	GameEnd() : Events(GAME_END)
	{
		std::cout << "GAME END\n";
	}
};

class MouseClick : public Events 
{
protected:

	std::pair<int, int> mousePos;	

public:

	MouseClick() : Events(MOUSE_CLICK) 
	{
		mousePos = { 0, 0 }; 

		std::cout << "MOUSE CLICK on X " + mousePos.first;
		std::cout << " and on Y " + mousePos.second;
		std::cout << "\n"; 
	}

	void setMousePos(std::pair<int, int> pos) { mousePos = pos; }

	nlohmann::json serializeToJSON() const;
};

