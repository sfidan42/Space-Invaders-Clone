#pragma once
#include <vector>
#include "ACharacter.hpp"

class MonsterCharacter : public ACharacter
{
public:
	MonsterCharacter(const Rectangle &srcTile, const Rectangle &destTile, const ACharacterDataType &data, const BulletSrcDataType &bulletSrc);
	~MonsterCharacter(void);
public:
	void	fireBullets(void);
	void	updateBulletLocations(void);
};

bool	allDead(const std::vector<ACharacter *> &monsters);
