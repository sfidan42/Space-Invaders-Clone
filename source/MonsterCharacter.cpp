#include "MonsterCharacter.hpp"

MonsterCharacter::MonsterCharacter(vec2 loc, float health, const float maxHealth, float damageValue, float speed)
 : ACharacter(loc, health, maxHealth, damageValue, speed) {}

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
