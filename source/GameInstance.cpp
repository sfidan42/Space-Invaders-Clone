#include "GameInstance.hpp"

static GameInstance	gameInstance;

float	GameInstance::getGameInstanceValue(GameInstanceValue InValueType) const
{
	unsigned int	valueIdx = static_cast<unsigned int>(InValueType);
	assert(valueIdx < values.size());
	return (values[valueIdx]);
}

void	GameInstance::setGameInstanceValue(const GameInstanceValue InValueType, const float InValue)
{
	unsigned int	valueIdx = static_cast<unsigned int>(InValueType);
	assert(valueIdx < values.size());
	values[valueIdx] = InValue;
}
