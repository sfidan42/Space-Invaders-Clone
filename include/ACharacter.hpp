#pragma once
# include "GameInstance.hpp"
# include <algorithm>

typedef struct
{
	float	x;
	float	y;
}			vec2;

class ACharacter
{
private:
	ACharacter(void);
protected:
	vec2		_loc;
	float		_health;
	const float	_maxHealth;
	bool		_isAlive;
	float		_damageValue;
	float		_speed;
public:
	ACharacter(vec2 loc, float health, const float maxHealth, float damageValue, float speed);
	ACharacter(const ACharacter &character);
	ACharacter	&operator=(const ACharacter &character);
	virtual ~ACharacter(void) = 0;
public:
	vec2	getLocation(void) const { return (_loc); }
	float	getHealth(void) const { return (_health); }
	bool	getIsAlive(void) const { return (_isAlive); };
	float	getDamageValue(void) const { return (_damageValue); }
	float	getSpeed(void) const { return (_speed); }
public:
	void	adjustLocation(const vec2 InLoc, const vec2 InBoundaries);
	void	adjustHealth(const float InHealth);
	void	setIsAlive(const bool InIsAlive);
	void	setDamageValue(const float InDamageValue);
	void	setSpeed(const float InSpeed);
};
