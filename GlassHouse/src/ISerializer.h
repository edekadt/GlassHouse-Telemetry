#pragma once
#ifdef GLASSHOUSE_EXPORTS
#define GLASSHOUSE_API __declspec(dllexport)
#else
#define GLASSHOUSE_API __declspec(dllimport)
#endif

#include <string>
class Event;

class GLASSHOUSE_API ISerializer
{
protected:

	ISerializer(): fileFormat(""), openingString(""), closingString("") {};

	~ISerializer() {};

	std::string fileFormat;
	std::string openingString;
	std::string closingString;

public:

	inline std::string getFileFormat() const { return fileFormat; };	// Returns the file extension for the format, including the '.'
	inline std::string getOpeningString() const { return ""; };		// Used by formats that require special file beginnings
	inline std::string getClosingString() const { return ""; };		// Used by formats that require special file end signifiers
	virtual void serialize(const Event& event, std::string& serializable) const = 0;	// Serialize single element
};
