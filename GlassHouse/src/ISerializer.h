#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

#include <string>

class GLASSHOUSE_API ISerializer
{
protected:

	ISerializer(): fileFormat("") {};

	~ISerializer() {};

	std::string fileFormat;	// The file extension for persistors that create files on a drive, including the '.'

public:

	inline std::string getFileFormat() const { return fileFormat; };
	virtual void serialize(std::string& serializable) const = 0;				// serialize single element
};
