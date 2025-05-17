#pragma once
# include "GameInstance.hpp"
# include <algorithm>
# include <nlohmann/json.hpp>
# include <raylib.h>

typedef struct
{
	float		health;
	float		maxHealth;
	bool		isAlive;
	float		damageValue;
	float		speed;
}				ACharacterDataType;

class ACharacter
{
private:
	ACharacter(void);
protected:
	Rectangle			_tile;
	ACharacterDataType	_data;
public:
	ACharacter(const Rectangle &tile, const ACharacterDataType &data);
	ACharacter(const Rectangle &tile, float health, const float maxHealth, float damageValue, float speed);
	ACharacter(const ACharacter &character);
	ACharacter	&operator=(const ACharacter &character);
	virtual ~ACharacter(void) = 0;
public:
	const Rectangle	&getDestTile(void) const { return (_tile); }
	float			getHealth(void) const { return (_data.health); }
	float			getMaxHealth(void) const { return (_data.maxHealth); }
	bool			getIsAlive(void) const { return (_data.isAlive); };
	float			getDamageValue(void) const { return (_data.damageValue); }
	float			getSpeed(void) const { return (_data.speed); }
public:
	void	adjustLocation(const float InIncX, const float InIncY, const Rectangle &InBoundaries);
	void	adjustHealth(const float InHealthIncr);
	void	adjustSpeed(const float InSpeedMult);
public:
	bool	checkHitWall(const Rectangle &InBoundaries);
};
