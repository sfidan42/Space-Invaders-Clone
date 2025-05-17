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

ACharacter::ACharacter(const Rectangle &tile, const ACharacterDataType &data)
{
	_tile = tile;
	_data.health = data.health;
	_data.maxHealth = data.maxHealth;
	_data.isAlive = true;
	_data.damageValue = data.damageValue;
	_data.speed = data.speed;
}

ACharacter::ACharacter(const Rectangle &tile, float health, float maxHealth, float damageValue, float speed)
{
	_tile = tile;
	_data.health = health;
	_data.maxHealth = maxHealth;
	_data.isAlive = true;
	_data.damageValue = damageValue;
	_data.speed = speed;
}

ACharacter::ACharacter(const ACharacter &character)
{
	_tile = character._tile;
	_data.health = character._data.health;
	_data.maxHealth = character._data.maxHealth;
	_data.isAlive = character._data.isAlive;
	_data.damageValue = character._data.damageValue;
	_data.speed = character._data.speed;
}

ACharacter	&ACharacter::operator=(const ACharacter &character)
{
	if (this != &character)
	{
		_tile = character._tile;
		_data.health = character._data.health;
		_data.maxHealth = character._data.maxHealth;
		_data.isAlive = character._data.isAlive;
		_data.damageValue = character._data.damageValue;
		_data.speed = character._data.speed;
	}
	return (*this);
}

ACharacter::~ACharacter(void) {} // Pure Virtual Destructor

void	ACharacter::adjustLocation(const float InIncX, const float InIncY, const Rectangle &InBoundaries)
{
	float	leftLimit = InBoundaries.x - _tile.width / 2;
	float	rightLimit = leftLimit + InBoundaries.width;
	float	upLimit = InBoundaries.y - _tile.height / 2;
	float	downLimit = upLimit + InBoundaries.height;

	_tile.x = std::clamp(_tile.x + InIncX, leftLimit, rightLimit);
	_tile.y = std::clamp(_tile.y + InIncY, upLimit, downLimit);
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
	float	leftLimit = InBoundaries.x - _tile.width / 2;
	float	rightLimit = leftLimit + InBoundaries.width;

	return (_tile.x <= leftLimit || rightLimit <= _tile.x);
}
