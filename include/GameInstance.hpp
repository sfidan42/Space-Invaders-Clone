#pragma once
# include <vector>
# include <fstream>
# include <sstream>
# include <cassert>

# define JSON_USE_IMPLICIT_CONVERSIONS 0
# include <nlohmann/json.hpp>

using json = nlohmann::json;

# define GAME_CONFIG(instance, keyPath, dataType) \
	instance->get(ConfigType::GAME, keyPath).template get<dataType>()

# define LEVEL_CONFIG(instance, keyPath, dataType) \
	instance->get(ConfigType::LEVEL, keyPath).template get<dataType>()

enum class ConfigType
{
	GAME,
	LEVEL,
};

class GameInstance
{
private:
	json	gameConfig;
	json	levelConfig;
private:
	static GameInstance	*instancePtr;
private:
	GameInstance() {}
public:
	// Deleting the copy constructor to prevent copies
	GameInstance(const GameInstance& obj) = delete;
	static GameInstance	*getInstance(void);
public:
	const json	get(const ConfigType InType, const std::string InPathKey);
	const json	get(const ConfigType InType);
	void		setGame(const std::string InGameConfigPath);
	void		setLevel(const std::string InLevelPath);
};
