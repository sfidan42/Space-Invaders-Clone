#include "ACharacter.hpp"

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

ACharacter::ACharacter(vec2 loc, float health, float maxHealth, float damageValue, float speed)
 : _maxHealth(maxHealth)
{
	_loc = loc;
	_health = health;
	_isAlive = true;
	_damageValue = damageValue;
	_speed = speed;
}

ACharacter::ACharacter(const ACharacter &character)
 : _maxHealth(character._maxHealth)
{
	_loc = character._loc;
	_health = character._health;
	_isAlive = character._isAlive;
	_damageValue = character._damageValue;
	_speed = character._speed;
}

ACharacter	&ACharacter::operator=(const ACharacter &character)
{
	if (this != &character)
		*this = character;
	return (*this);
}

ACharacter::~ACharacter(void) {} // Pure Virtual Destructor

void	ACharacter::adjustLocation(const vec2 InLoc, const vec2 InBoundaries)
{
	_loc.x = std::clamp(_loc.x + InLoc.x, 0.0f, InBoundaries.x);
	_loc.y = std::clamp(_loc.y + InLoc.y, 0.0f, InBoundaries.y);
}

void	ACharacter::adjustHealth(const float InHealth)
{
	_health = std::clamp(_health + InHealth, 0.0f, _maxHealth);
}

void	ACharacter::setIsAlive(const bool InIsAlive)
{
	_isAlive = InIsAlive;
}

void	ACharacter::setDamageValue(const float InDamageValue)
{
	_damageValue = InDamageValue;
}

void	ACharacter::setSpeed(const float InSpeed)
{
	_damageValue = InSpeed;
}
