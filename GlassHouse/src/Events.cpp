#include "Events.h"

nlohmann::json Events::serializeToJSON() const
{
	nlohmann::json data = {
            {"Evento", std::to_string(gameEvent)},
            {"Tiempo", time}
    };

    return data; 
}

nlohmann::json MouseClick::serializeToJSON() const
{
    nlohmann::json data = Events::serializeToJSON(); 

    data.push_back({ { "Pos X", mousePos.first }, { "Pos Y", mousePos.second } });

    return data;
}