#pragma once
# include <raylib.h>
# include <ACharacter.hpp>
# include <cassert>
# include <nlohmann/json.hpp>

using json = nlohmann::json;

inline void	to_json(json &j, const Rectangle &rect)
{
	std::vector<float>	rectVec = {rect.x, rect.y, rect.width, rect.height};
	j = rectVec;
}

inline void	from_json(const json &j, Rectangle &rect)
{
	assert(j.size() == 4);
	j.at(0).get_to(rect.x);
	j.at(1).get_to(rect.y);
	j.at(2).get_to(rect.width);
	j.at(3).get_to(rect.height);
}

inline void	to_json(json &j, const ACharacterDataType &data)
{
	json	d;

	d["health"] = data.health;
	d["maxHealth"] = data.maxHealth;
	d["speed"] = data.speed;
	d["isAlive"] = data.isAlive;
	j["data"] = d;
}

inline void	from_json(const json &j, ACharacterDataType &data)
{
	assert(!j.empty());
	assert(j.contains("health"));
	assert(j.contains("maxHealth"));
	assert(j.contains("speed"));

	j.at("health").get_to(data.health);
	j.at("maxHealth").get_to(data.maxHealth);
	j.at("speed").get_to(data.speed);
	data.isAlive = true;
}
