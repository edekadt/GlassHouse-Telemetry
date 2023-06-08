#include "Event.h"

Event::Event()
{
    content = std::unordered_map<std::string, Serializable*>();
}

Event::~Event()
{
    for (auto i = content.begin(); i != content.end(); ++i)
    {
        delete(i->second);
        i->second = nullptr;
    }
}

Event Event::add(std::string key, int32_t val)
{
    content.insert({ key, new Serializable(val) });
    return *this;
}

Event Event::add(std::string key, double val)
{
    content.insert({ key, new Serializable(val) });
    return *this;
}

Event Event::add(std::string key, std::string val)
{
    content.insert({ key, new Serializable(val) });
    return *this;
}

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
