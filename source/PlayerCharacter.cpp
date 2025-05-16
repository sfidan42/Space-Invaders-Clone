#include "PlayerCharacter.hpp"

PlayerCharacter::PlayerCharacter(const Rectangle &tile, const ACharacterDataType &data)
 : ACharacter(tile, data.health, data.maxHealth, data.damageValue, data.speed) {}

PlayerCharacter::PlayerCharacter(const Rectangle &tile, float health, const float maxHealth, float damageValue, float speed)
 : ACharacter(tile, health, maxHealth, damageValue, speed) {}

PlayerCharacter::~PlayerCharacter(void) {}
