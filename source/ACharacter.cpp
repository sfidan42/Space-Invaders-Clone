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

ACharacter::ACharacter(const Rectangle &srcTile, const Rectangle &destTile, const ACharacterDataType &data, const BulletSrcDataType &bulletSrc)
{
	_srcTile = srcTile;
	_destTile = destTile;
	_data = data;
	_bulletSrc = bulletSrc;
}

ACharacter::ACharacter(const ACharacter &character)
{
	_srcTile = character._srcTile;
	_destTile = character._destTile;
	_data = character._data;
	_bulletSrc = character._bulletSrc;
}

ACharacter	&ACharacter::operator=(const ACharacter &character)
{
	if (this != &character)
	{
		_srcTile = character._srcTile;
		_destTile = character._destTile;
		_data = character._data;
		_bulletSrc = character._bulletSrc;
	}
	return (*this);
}

ACharacter::~ACharacter(void) {} // Pure Virtual Destructor

void	ACharacter::adjustLocation(const float InIncX, const float InIncY, const Rectangle &InBoundaries)
{
	if (_data.isAlive)
	{
		float	leftLimit = InBoundaries.x - _destTile.width / 2;
		float	rightLimit = leftLimit + InBoundaries.width;
		float	upLimit = InBoundaries.y - _destTile.height / 2;
		float	downLimit = upLimit + InBoundaries.height;

		_destTile.x = std::clamp(_destTile.x + InIncX, leftLimit, rightLimit);
		_destTile.y = std::clamp(_destTile.y + InIncY, upLimit, downLimit);
	}
}

void	ACharacter::adjustHealth(const float InHealthIncr)
{
	float	minHealth = 0.0f;

	_data.health = std::clamp(_data.health + InHealthIncr, minHealth, _data.maxHealth);
	if (_data.health <= minHealth)
	{
		_data.isAlive = false;
	}
}

void	ACharacter::adjustSpeed(const float InSpeedMult)
{
	if (_data.isAlive)
	{
		_data.speed *= InSpeedMult;
	}
}

bool	ACharacter::checkHitWall(const Rectangle &InBoundaries)
{
	if (_data.isAlive)
	{
		float	leftLimit = InBoundaries.x - _destTile.width / 2;
		float	rightLimit = leftLimit + InBoundaries.width;
		
		return (_destTile.x <= leftLimit || rightLimit <= _destTile.x);
	}
	return (false);
}

bool	ACharacter::checkHitFloor(const Rectangle &InBoundaries)
{
	if (_data.isAlive)
	{
		float	topLimit = InBoundaries.y - _destTile.height / 2;
		float	bottomLimit = topLimit + InBoundaries.height;
	
		return (bottomLimit <= _destTile.y);
	}
	return (false);
}

void	ACharacter::changeTiles(const Rectangle &srcTile, const Rectangle &destTile)
{
	_srcTile = srcTile;
	_destTile.width = destTile.width;
	_destTile.height = destTile.height;
}

static inline bool valueInRange(int value, int min, int max)
{
	return (value >= min) && (value <= max);
}

static inline bool rectOverlap(const Rectangle &A, const Rectangle &B)
{
	bool xOverlap = valueInRange(A.x, B.x, B.x + B.width) ||
					valueInRange(B.x, A.x, A.x + A.width);

	bool yOverlap = valueInRange(A.y, B.y, B.y + B.height) ||
					valueInRange(B.y, A.y, A.y + A.height);

	return xOverlap && yOverlap;
}

bool	ACharacter::amIHitByYourBullet(ACharacter *character)
{
	assert(character != NULL);

	std::list<BulletDestDataType>	&bullets = character->getBulletDestTiles();
	for (BulletDestDataType &bullet : bullets)
	{
		if (!bullet.isActive || !_data.isAlive)
		{
			continue ;
		}
		if (rectOverlap(bullet.tile, _destTile))
		{
			this->adjustHealth(0.0f - character->getBulletSrc().damage);
			if (!this->getIsAlive())
			{
				bullet.isActive = false;
			}
			return (true);
		}
	}
	return (false);
}
