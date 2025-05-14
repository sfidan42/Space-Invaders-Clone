#pragma once
#include <vector>
#include "ACharacter.hpp"

class MonsterCharacter : public ACharacter
{
public:
	MonsterCharacter(vec2 loc, float health, const float maxHealth, float damageValue, float speed);
	~MonsterCharacter(void);
};

bool	allDead(const std::vector<ACharacter *> &monsters);
