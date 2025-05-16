#pragma once
#include "ACharacter.hpp"

class PlayerCharacter : public ACharacter
{
public:
	PlayerCharacter(const Rectangle &tile, const ACharacterDataType &data);
	PlayerCharacter(const Rectangle &tile, float health, const float maxHealth, float damageValue, float speed);
	~PlayerCharacter(void);
};
