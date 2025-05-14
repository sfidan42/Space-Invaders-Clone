#include "PlayerCharacter.hpp"

PlayerCharacter::PlayerCharacter(vec2 loc, float health, const float maxHealth, float damageValue, float speed)
 : ACharacter(loc, health, maxHealth, damageValue, speed) {}

PlayerCharacter::~PlayerCharacter(void) {}
