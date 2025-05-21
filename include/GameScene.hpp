#pragma once
# include "Scene.hpp"
# include "PlayerCharacter.hpp"
# include "MonsterCharacter.hpp"
# include <vector>
# include <raylib.h>

class GameScene : public Scene
{
private:
	Texture2D					_texture;
	std::vector<Sound>			_sounds;
	std::vector<ACharacter *>	_monsters;
	ACharacter					*_player;
	Rectangle					_enemyBoundaries;
	Rectangle					_playerBoundaries;
	Rectangle					_explosionSrcTile;
	Rectangle					_explosionDestTile;
private:
	float	_speedXDirection;
	float	_locationYOffset;
	float	_playerStep;
	float	_cellWidth;
	float	_cellheight;
private:
	void	initMonsters(void);
	void	initPlayer(void);
	void	initTextures(void);
	void	initSounds(void);
	void	initBoundaries(void);
public:
	GameScene();
	~GameScene();
	void	eventHandler(void);
	void	drawingHandler(void);
};
