#include "Event.h"
#include <Serializable.h>

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

SessionStart::SessionStart(size_t sessionID_) : Event("SESSION_START")
{
    GameStart::gameCount = 0;
    GameEnd::gameCount = 0;
    add("SessionID", sessionID_);
}

Event* Event::add(std::string key, size_t val)
{
    content.insert({ key, new Serializable(val) });
    return this;
}

Event* Event::add(std::string key, int32_t val)
{
    content.insert({ key, new Serializable(val) });
    return this;
}

Event* Event::add(std::string key, double val)
{
    content.insert({ key, new Serializable(val) });
    return this;
}

Event* Event::add(std::string key, std::string val)
{
    content.insert({ key, new Serializable(val) });
    return this;
}

Event* Event::add(std::string key, bool val)
{
    content.insert({ key, new Serializable(val) });
    return this;
}


int32_t GameStart::gameCount = 0;
int32_t GameEnd::gameCount = 0;