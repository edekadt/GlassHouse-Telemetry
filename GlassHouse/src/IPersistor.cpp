#include <IPersistor.h>
#include <ISerializer.h>
#include <string>

bool IPersistor::write(Event* event)
{
	std::string formattedString = "";
	serializer->serialize(*event, formattedString);

	persist(formattedString);
	return true;
}
