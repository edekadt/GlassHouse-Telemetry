#include "Event.h"

nlohmann::json Event::serializeToJSON() const
{
	nlohmann::json data = {
            {"Event", std::to_string(id)},
            {"Time", time}
    };

    return data; 
}

nlohmann::json MouseClick::serializeToJSON() const
{
    nlohmann::json data = Event::serializeToJSON(); 

    data.push_back({ { "Position X", mousePos.first }, { "Position Y", mousePos.second } });

    return data;
}