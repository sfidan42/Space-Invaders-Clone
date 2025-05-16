#pragma once
#include <vector>
#include "ACharacter.hpp"

class MonsterCharacter : public ACharacter
{
public:
	MonsterCharacter(const Rectangle &tile, const ACharacterDataType &data);
	MonsterCharacter(const Rectangle &tile, float health, const float maxHealth, float damageValue, float speed);
	~MonsterCharacter(void);
};

bool	allDead(const std::vector<ACharacter *> &monsters);
