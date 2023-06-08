#include <JsonSerializer.h>

JsonSerializer::JsonSerializer() : ISerializer()
{
	fileFormat = ".json";
	openingString = "";
	separator = "";
	closingString = "";
}

void JsonSerializer::serialize(const Event& event, std::string& serializable) const
{

}
