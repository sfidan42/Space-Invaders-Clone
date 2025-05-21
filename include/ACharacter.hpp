#pragma once
# include "GameInstance.hpp"
# include <algorithm>
# include <nlohmann/json.hpp>
# include <raylib.h>
# include <list>

typedef struct
{
	float		health;
	float		maxHealth;
	bool		isAlive;
	float		speed;
}				ACharacterDataType;

typedef struct
{
	Rectangle	srcTile;
	Vector2		destSize;
	float		damage;
	float		speed;
}				BulletSrcDataType;

typedef struct
{
	Rectangle	tile;
	bool		isActive;
}				BulletDestDataType;

class ACharacter
{
private:
	ACharacter(void);
protected:
	Rectangle						_srcTile;
	Rectangle						_destTile;
	ACharacterDataType				_data;
	BulletSrcDataType				_bulletSrc;
	std::list<BulletDestDataType>	_bulletDestTiles;
public:
	ACharacter(const Rectangle &srcTile, const Rectangle &destTile, const ACharacterDataType &data, const BulletSrcDataType &bulletSrc);
	ACharacter(const ACharacter &character);
	ACharacter	&operator=(const ACharacter &character);
	virtual ~ACharacter(void) = 0;
public:
	const Rectangle					&getSrcTile(void) const { return (_srcTile); }
	const Rectangle					&getDestTile(void) const { return (_destTile); }
	float							getHealth(void) const { return (_data.health); }
	float							getMaxHealth(void) const { return (_data.maxHealth); }
	bool							getIsAlive(void) const { return (_data.isAlive); };
	float							getSpeed(void) const { return (_data.speed); }
	const BulletSrcDataType			&getBulletSrc(void) const { return (_bulletSrc); }
	std::list<BulletDestDataType>	&getBulletDestTiles(void) { return (_bulletDestTiles); }
public:
	void	adjustLocation(const float InIncX, const float InIncY, const Rectangle &InBoundaries);
	void	adjustHealth(const float InHealthIncr);
	void	adjustSpeed(const float InSpeedMult);
public:
	void	changeTiles(const Rectangle &srcTile, const Rectangle &destTile);
public:
	bool	checkHitWall(const Rectangle &InBoundaries);
	bool	checkHitFloor(const Rectangle &InBoundaries);
public:
	virtual void	fireBullets(void) = 0;
	virtual void	updateBulletLocations(void) = 0;
	bool			amIHitByYourBullet(ACharacter *character);
};
