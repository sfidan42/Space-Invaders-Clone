#include "MonsterCharacter.hpp"

MonsterCharacter::MonsterCharacter(const Rectangle &srcTile, const Rectangle &destTile, const ACharacterDataType &data)
 : ACharacter(srcTile, destTile, data) {}

MonsterCharacter::MonsterCharacter(const Rectangle &srcTile, const Rectangle &destTile, float health, const float maxHealth, float damageValue, float speed)
 : ACharacter(srcTile, destTile, health, maxHealth, damageValue, speed) {}

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
