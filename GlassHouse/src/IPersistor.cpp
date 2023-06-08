#include <IPersistor.h>
#include <ISerializer.h>
#include <string>

bool IPersistor::write(std::vector<Event*> events)
{
	open();
	std::string formattedString;
	for (Event* e : events)
	{
		std::string s = "";
		serializer->serialize(*e, s);
		formattedString.append(s);
	}
	persist(formattedString);
	close();
	return true;
}
