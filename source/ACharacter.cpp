#include "ACharacter.hpp"
#include <iostream>

/*
ACharacter::ACharacter(void)
{
	loc = { .loc_x = -1.0f, .loc_y = -1.0f }; // later can be expanded into 3D
	health = 0.0f; // percentage logic
	isAlive = true; // No dead born!
	damageValue = 0.0f; // Not all kinds of characters are aggressive
	speed = 0.0f; // No one is moving by default
}
*/

ACharacter::ACharacter(const Rectangle &srcTile, const Rectangle &destTile, const ACharacterDataType &data)
{
	_srcTile = srcTile;
	_destTile = destTile;
	_data = data;
	_data.isAlive = true;
}

ACharacter::ACharacter(const Rectangle &srcTile, const Rectangle &destTile, float health, float maxHealth, float damageValue, float speed)
{
	_srcTile = srcTile;
	_destTile = destTile;
	_data = {
		.health = health,
		.maxHealth = maxHealth,
		.isAlive = true,
		.damageValue = damageValue,
		.speed = speed
	};
}

ACharacter::ACharacter(const ACharacter &character)
{
	_srcTile = character._srcTile;
	_destTile = character._destTile;
	_data = character._data;
}

ACharacter	&ACharacter::operator=(const ACharacter &character)
{
	if (this != &character)
	{
		_srcTile = character._srcTile;
		_destTile = character._destTile;
		_data = character._data;
	}
	return (*this);
}

ACharacter::~ACharacter(void) {} // Pure Virtual Destructor

void	ACharacter::adjustLocation(const float InIncX, const float InIncY, const Rectangle &InBoundaries)
{
	float	leftLimit = InBoundaries.x - _destTile.width / 2;
	float	rightLimit = leftLimit + InBoundaries.width;
	float	upLimit = InBoundaries.y - _destTile.height / 2;
	float	downLimit = upLimit + InBoundaries.height;

	_destTile.x = std::clamp(_destTile.x + InIncX, leftLimit, rightLimit);
	_destTile.y = std::clamp(_destTile.y + InIncY, upLimit, downLimit);
}

void	ACharacter::adjustHealth(const float InHealthIncr)
{
	_data.health = std::clamp(_data.health + InHealthIncr, 0.0f, _data.maxHealth);
}

void	ACharacter::adjustSpeed(const float InSpeedMult)
{
	_data.speed *= InSpeedMult;
}

bool	ACharacter::checkHitWall(const Rectangle &InBoundaries)
{
	float	leftLimit = InBoundaries.x - _destTile.width / 2;
	float	rightLimit = leftLimit + InBoundaries.width;

	return (_destTile.x <= leftLimit || rightLimit <= _destTile.x);
}

bool	ACharacter::checkHitFloor(const Rectangle &InBoundaries)
{
	float	topLimit = InBoundaries.y - _destTile.height / 2;
	float	bottomLimit = topLimit + InBoundaries.height;

	return (bottomLimit <= _destTile.y);
}
