#pragma once
#include "ACharacter.hpp"

class PlayerCharacter : public ACharacter
{
public:
	PlayerCharacter(vec2 loc, float health, const float maxHealth, float damageValue, float speed);
	~PlayerCharacter(void);
};
