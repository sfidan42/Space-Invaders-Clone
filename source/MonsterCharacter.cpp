#include "MonsterCharacter.hpp"

MonsterCharacter::MonsterCharacter(const Rectangle &tile, const ACharacterDataType &data)
 : ACharacter(tile, data) {}

MonsterCharacter::MonsterCharacter(const Rectangle &tile, float health, const float maxHealth, float damageValue, float speed)
 : ACharacter(tile, health, maxHealth, damageValue, speed) {}

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
