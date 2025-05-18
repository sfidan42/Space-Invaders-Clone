#include "PlayerCharacter.hpp"

PlayerCharacter::PlayerCharacter(const Rectangle &srcTile, const Rectangle &destTile, const ACharacterDataType &data)
 : ACharacter(srcTile, destTile, data.health, data.maxHealth, data.damageValue, data.speed) {}

PlayerCharacter::PlayerCharacter(const Rectangle &srcTile, const Rectangle &destTile, float health, const float maxHealth, float damageValue, float speed)
 : ACharacter(srcTile, destTile, health, maxHealth, damageValue, speed) {}

PlayerCharacter::~PlayerCharacter(void) {}
