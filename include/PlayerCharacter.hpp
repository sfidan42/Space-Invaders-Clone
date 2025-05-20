#pragma once
#include "ACharacter.hpp"

class PlayerCharacter : public ACharacter
{
public:
	PlayerCharacter(const Rectangle &srcTile, const Rectangle &destTile, const ACharacterDataType &data, const BulletSrcDataType &bulletSrc);
	~PlayerCharacter(void);
public:
	void	fireBullets(void);
	void	updateBulletLocations(void);
};
