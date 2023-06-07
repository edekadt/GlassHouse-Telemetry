#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

#include <vector>

class ISerializer;
class Event;

class GLASSHOUSE_API IPersistor
{
protected:
	ISerializer* serializer;

	IPersistor(ISerializer* serializer_): serializer(serializer_) {};
	
	~IPersistor() { serializer = nullptr; };

	virtual void persist(const std::string& s) const = 0;

public:
	virtual void begin() {};	// Write file start
	virtual void end() {};		// Write file ending
	bool write(std::vector<Event*> events) const;	// Returns true on successful persistence
};
