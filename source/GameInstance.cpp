#include "GameInstance.hpp"

GameInstance	*GameInstance::instancePtr = new GameInstance();

GameInstance	*GameInstance::getInstance(void)
{
	return (instancePtr);
}

const json	GameInstance::get(const ConfigType InType, const std::string InPathKey)
{
	json	config;

	assert(!InPathKey.empty());
	
	switch (InType)
	{
		case ConfigType::GAME: config = gameConfig; break;
		case ConfigType::LEVEL: config = levelConfig; break;
		default: break;
	}

	assert(!config.empty());

	std::istringstream	iss(InPathKey);
	std::string			key;

	while (std::getline(iss, key, '.'))
	{
		assert(config.contains(key));
		config = config[key];
	}
	return (config);
}

const json	GameInstance::get(const ConfigType InType)
{
	json	config;

	switch (InType)
	{
		case ConfigType::GAME: config = gameConfig; break;
		case ConfigType::LEVEL: config = levelConfig; break;
		default: break;
	}
	assert(!config.empty());
	return (config);
}

void	GameInstance::setGame(const std::string InGameConfigPath)
{
	std::ifstream	gameF(InGameConfigPath);
	
	assert(gameF.is_open());

	this->gameConfig = json::parse(gameF);
	gameF.close();
}

void	GameInstance::setLevel(const std::string InLevelPath)
{
	std::ifstream	levelF(InLevelPath);

	assert(levelF.is_open());

	this->levelConfig = json::parse(levelF);
	levelF.close();
}
