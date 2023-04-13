#include "Events.h"

#include <nlohmann/json.hpp>

std::string Events::serializeToJSON() const
{
	nlohmann::json data = {
            {"Evento", std::to_string(gameEvent)},
            {"Tiempo", time}
    };

    std::string information = data.dump(); 

    return information; 
}

std::string MouseClick::serializeToJSON() const
{
    std::string intro = Events::serializeToJSON(); 

    nlohmann::json data = {
            {"Pos X", mousePos.first},
            {"Pos Y", mousePos.second}
    };

    std::string information = intro + data.dump();

    return information;
}