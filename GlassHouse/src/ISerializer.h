#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

#include <list>
#include <vector>

template <class T>
class GLASSHOUSE_API ISerializer
{
protected:

	ISerializer() {};

	~ISerializer() {};

public:

	virtual void serialize(T& serializable) = 0;				// serialize single element
	virtual void serialize(T&* serializables) = 0;				// serialize dynamic array of elements
	virtual void serialize(T&[] serializables) = 0;				// serialize static array of elements
	virtual void serialize(std::vector<T> serializables) = 0;	// serialize vector of elements
	virtual void serialize(std::list<T> serializables) = 0;		// serialize list of elements
};
