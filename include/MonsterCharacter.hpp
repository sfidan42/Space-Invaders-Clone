#pragma once
#include <vector>
#include "ACharacter.hpp"

class MonsterCharacter : public ACharacter
{
private:
	Rectangle	_srcTile;
public:
	MonsterCharacter(const Rectangle &srcTile, const Rectangle &destTile, const ACharacterDataType &data);
	MonsterCharacter(const Rectangle &srcTile, const Rectangle &destTile, float health, const float maxHealth, float damageValue, float speed);
	~MonsterCharacter(void);
};

bool	allDead(const std::vector<ACharacter *> &monsters);
