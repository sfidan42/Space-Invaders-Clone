#include "PlayerCharacter.hpp"

PlayerCharacter::PlayerCharacter(const Rectangle &srcTile, const Rectangle &destTile, const ACharacterDataType &data, const BulletSrcDataType &bulletSrc)
 : ACharacter(srcTile, destTile, data, bulletSrc) {}

PlayerCharacter::~PlayerCharacter(void) {}

void	PlayerCharacter::fireBullets(void)
{
	Rectangle	bullet;

	bullet.width = _bulletSrc.destSize.x;
	bullet.height = _bulletSrc.destSize.y;

	bullet.x = _destTile.x;
	bullet.y = _destTile.y;
	_bulletDestTiles.push_back(bullet);

	bullet.x += _destTile.width;
	_bulletDestTiles.push_back(bullet);
}

void	PlayerCharacter::updateBulletLocations(void)
{
	for (Rectangle &bullet : _bulletDestTiles)
	{
		bullet.y -= _bulletSrc.speed;
	}
}
