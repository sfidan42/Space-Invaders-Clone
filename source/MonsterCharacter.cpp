#include "MonsterCharacter.hpp"

MonsterCharacter::MonsterCharacter(const Rectangle &srcTile, const Rectangle &destTile, const ACharacterDataType &data, const BulletSrcDataType &bulletSrc)
 : ACharacter(srcTile, destTile, data, bulletSrc) {}

MonsterCharacter::~MonsterCharacter(void) {}

bool    allDead(const std::vector<ACharacter *> &monsters)
{
	for (ACharacter * monster : monsters)
	{
		if (monster->getIsAlive())
		{
			return (false);
		}
	}
	return (true);
}

void	MonsterCharacter::fireBullets(void)
{
}

void	MonsterCharacter::updateBulletLocations(void)
{
}
