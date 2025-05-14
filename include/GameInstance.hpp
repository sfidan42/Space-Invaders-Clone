#pragma once
# include <vector>
# include <cassert>

enum class GameInstanceValue
{
	WINDOW_HEIGHT,
	WINDOW_WIDTH,
	H_MARGIN,
	V_MARGIN,
};

class GameInstance
{
private:
	std::vector<float>	values = { 300.0f, 250.0f, 15.0f, 25.0f };
public:
	float	getGameInstanceValue(GameInstanceValue InValueType) const;
	void	setGameInstanceValue(const GameInstanceValue InValueType, const float InValue);
};
