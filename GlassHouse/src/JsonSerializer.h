#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

#include <string>
#include <ISerializer.h>
class Event;

class GLASSHOUSE_API JsonSerializer: public ISerializer
{
public:
	JsonSerializer();

	~JsonSerializer() {}

	virtual void serialize(const Event& event, std::string& serializable) const;	// Serialize single element
};
