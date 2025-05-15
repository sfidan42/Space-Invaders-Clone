#pragma once
# include <vector>
# include <fstream>
# include <sstream>
# include <cassert>
# include <nlohmann/json.hpp>

using json = nlohmann::json;

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
	const json	get(const ConfigType InType, const std::string InKey);
	void		setGame(const std::string InGameConfigPath);
	void		setLevel(const std::string InLevelPath);
};
