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
	Rectangle			_srcTile;
	Rectangle			_destTile;
	ACharacterDataType	_data;
public:
	ACharacter(const Rectangle &srcTile, const Rectangle &destTile, const ACharacterDataType &data);
	ACharacter(const Rectangle &srcTile, const Rectangle &destTile, float health, const float maxHealth, float damageValue, float speed);
	ACharacter(const ACharacter &character);
	ACharacter	&operator=(const ACharacter &character);
	virtual ~ACharacter(void) = 0;
public:
	const Rectangle	&getSrcTile(void) const { return (_srcTile); }
	const Rectangle	&getDestTile(void) const { return (_destTile); }
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
	bool	checkHitFloor(const Rectangle &InBoundaries);
};
