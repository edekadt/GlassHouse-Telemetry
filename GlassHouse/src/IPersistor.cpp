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

void IPersistor::setId(size_t id)
{
	this->id = id;
}
