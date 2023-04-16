#include "Events.h"

nlohmann::json Events::serializeToJSON() const
{
	nlohmann::json data = {
            {"Event", std::to_string(gameEvent)},
            {"Time", time}
    };

    return data; 
}

nlohmann::json MouseClick::serializeToJSON() const
{
    nlohmann::json data = Events::serializeToJSON(); 

    data.push_back({ { "Position X", mousePos.first }, { "Position Y", mousePos.second } });

    return data;
}