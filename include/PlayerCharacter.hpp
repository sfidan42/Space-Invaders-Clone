#pragma once
#include "ACharacter.hpp"

class PlayerCharacter : public ACharacter
{
public:
	PlayerCharacter(const Rectangle &srcTile, const Rectangle &destTile, const ACharacterDataType &data);
	PlayerCharacter(const Rectangle &srcTile, const Rectangle &destTile, float health, const float maxHealth, float damageValue, float speed);
	~PlayerCharacter(void);
};
