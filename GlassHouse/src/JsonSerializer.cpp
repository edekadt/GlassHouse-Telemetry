#include <JsonSerializer.h>
#include <Event.h>
#include <Serializable.h>
#include <nlohmann/json.hpp>

JsonSerializer::JsonSerializer() : ISerializer()
{
	fileFormat = ".json";
	openingString = "";
	separator = "";
	closingString = "";
}

void JsonSerializer::serialize(const Event& event, std::string& serializable) const
{
	nlohmann::json jsonObj = {};

	const auto& content = event.getContent();

	jsonObj.push_back({ "EventID", event.getType() });

	for (auto& it : content) {
		jsonObj.push_back({ it.first, it.second->toString() });
	}

	serializable += jsonObj.dump(4);
}
