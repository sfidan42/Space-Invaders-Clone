#include "PlayerCharacter.hpp"

PlayerCharacter::PlayerCharacter(const Rectangle &srcTile, const Rectangle &destTile, const ACharacterDataType &data, const BulletSrcDataType &bulletSrc)
 : ACharacter(srcTile, destTile, data, bulletSrc) {}

PlayerCharacter::~PlayerCharacter(void) {}

void	PlayerCharacter::fireBullets(void)
{
	BulletDestDataType	bullet;

	bullet.isActive = true;

	bullet.tile.width = _bulletSrc.destSize.x;
	bullet.tile.height = _bulletSrc.destSize.y;

	bullet.tile.x = _destTile.x;
	bullet.tile.y = _destTile.y;
	_bulletDestTiles.push_back(bullet);

	bullet.tile.x += _destTile.width;
	_bulletDestTiles.push_back(bullet);
}

void	PlayerCharacter::updateBulletLocations(void)
{
	for (BulletDestDataType &bullet : _bulletDestTiles)
	{
		if (bullet.isActive)
		{
			bullet.tile.y -= _bulletSrc.speed;
		}
	}
}
