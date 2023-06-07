#include <IPersistor.h>
#include <ISerializer.h>
#include <string>

bool IPersistor::write() const
{
	std::string formattedString = serializer->serialize();
	return true;
}
