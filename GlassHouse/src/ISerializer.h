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

	ISerializer(): fileFormat(""), openingString(""), separator(""), closingString("") {};

	std::string fileFormat;
	std::string openingString;
	std::string separator;
	std::string closingString;

public:
	virtual ~ISerializer() {};
	inline std::string getFileFormat() const { return fileFormat; };	// Returns the file extension for the format, including the '.'
	inline std::string getOpeningString() const { return openingString; };		// Used by formats that require special file beginnings
	inline std::string getSeparator() const { return separator; };				// Character string that separates two serialized events
	inline std::string getClosingString() const { return closingString; };		// Used by formats that require special file end signifiers
	virtual void serialize(const Event& event, std::string& serializable) const = 0;	// Returns a single element serialized as a string
};
