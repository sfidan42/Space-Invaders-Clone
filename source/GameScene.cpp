#include "GameScene.hpp"
#include "Conversions.hpp"

void	GameScene::initMonsters(void)
{
	GameInstance	*game = GameInstance::getInstance();

	std::vector<unsigned int>	monsterCounts = game->get(ConfigType::LEVEL, "monsterCounts").template get<std::vector<unsigned int>>();	std::vector<unsigned int>	monsterTypes = game->get(ConfigType::LEVEL, "monsterTypes").template get<std::vector<unsigned int>>();

	assert(monsterCounts.size() == monsterTypes.size());

	const int	totalNumMonsters = std::accumulate(monsterCounts.begin(), monsterCounts.end(), 0);
	
	_monsters.reserve(totalNumMonsters);

	ACharacterDataType		monsterData = game->get(ConfigType::LEVEL, "monster.data").template get<ACharacterDataType>();
	float					resizeRatio = game->get(ConfigType::GAME, "textures.resizeRatio").template get<float>();
	std::vector<Rectangle>	monsterSrcTiles = game->get(ConfigType::GAME, "textures.sourceTiles.monsters").template get<std::vector<Rectangle>>();
	std::vector<Rectangle>	monsterDestTiles;

	monsterDestTiles.reserve(monsterSrcTiles.size());
	for (Rectangle &monsterSrcTile : monsterSrcTiles)
	{
		Rectangle	monsterDestTile = {
			.x = 0.0f,
			.y = 0.0f,
			.width = monsterSrcTile.width * resizeRatio,
			.height = monsterSrcTile.height * resizeRatio
		};
		monsterDestTiles.push_back(monsterDestTile);
	}

	json	cell = game->get(ConfigType::GAME, "textures.sourceTiles.cell");
	_cellWidth = cell["width"].template get<const float>();
	_cellHeigth = cell["heigth"].template get<const float>();

	for (unsigned int	monsterCountIdx = 0; monsterCountIdx < monsterCounts.size(); monsterCountIdx++)
	{
		unsigned int	monsterCount = monsterCounts[monsterCountIdx];

		for (unsigned int rowCountIdx = 0; rowCountIdx < monsterCount; rowCountIdx++)
		{
			const unsigned int	monsterType = monsterTypes[monsterCountIdx];

			assert(monsterType < monsterSrcTiles.size());

			Rectangle	monsterSrcTile = monsterSrcTiles[monsterType];
			Rectangle	monsterDestTile = monsterDestTiles[monsterType];

			monsterDestTile.x = _enemyBoundaries.x + _cellWidth * rowCountIdx - monsterDestTile.width / 2;
			monsterDestTile.y = _enemyBoundaries.y + _cellHeigth * monsterCountIdx - monsterDestTile.height / 2;

			ACharacter	*monster = new MonsterCharacter(monsterSrcTile, monsterDestTile, monsterData);
			_monsters.push_back(monster);
		}
	}
}

void	GameScene::initPlayer(void)
{
	GameInstance	*game = GameInstance::getInstance();

	ACharacterDataType	playerData = game->get(ConfigType::LEVEL, "player.data").template get<ACharacterDataType>();
	Rectangle			playerSrcTile = game->get(ConfigType::GAME, "textures.sourceTiles.rocket").template get<Rectangle>();
	Rectangle			playerDestTile;

	float	resizeRatio = game->get(ConfigType::GAME, "textures.resizeRatio").template get<float>();
	
	json	playerLocation = game->get(ConfigType::LEVEL, "player.location");
	playerDestTile.x = playerLocation["horizontal"].template get<float>();
	playerDestTile.y = playerLocation["vertical"].template get<float>();
	playerDestTile.width = playerSrcTile.width * resizeRatio;
	playerDestTile.height = playerSrcTile.height * resizeRatio;

	const unsigned int	screenW = game->get(ConfigType::GAME, "windows.main.width").template get<const unsigned int>();
	const unsigned int	screenH = game->get(ConfigType::GAME, "windows.main.height").template get<const unsigned int>();

	playerDestTile.x *= screenW;
	playerDestTile.y *= screenH;
	playerDestTile.x -= playerDestTile.width / 2;
	playerDestTile.y -= playerDestTile.height / 2;

	_player = new PlayerCharacter(playerSrcTile, playerDestTile, playerData);
}

GameScene::GameScene() : Scene()
{
	GameInstance	*game = GameInstance::getInstance();

	std::string	texturePath = game->get(ConfigType::GAME, "textures.SpaceInvaders").template get<std::string>();
	
	_texture = LoadTexture(texturePath.c_str());

	_enemyBoundaries = game->get(ConfigType::GAME, "windows.enemies").template get<Rectangle>();
	_playerBoundaries = game->get(ConfigType::GAME, "windows.player").template get<Rectangle>();

	const unsigned int	screenW = game->get(ConfigType::GAME, "windows.main.width").template get<const unsigned int>();
	const unsigned int	screenH = game->get(ConfigType::GAME, "windows.main.height").template get<const unsigned int>();

	_enemyBoundaries.x *= screenW;
	_enemyBoundaries.y *= screenH;
	_enemyBoundaries.width *= screenW;
	_enemyBoundaries.height *= screenH;

	_playerBoundaries.x *= screenW;
	_playerBoundaries.y *= screenH;
	_playerBoundaries.width *= screenW;
	_playerBoundaries.height *= screenH;

	initMonsters();
	initPlayer();

	InitAudioDevice();

	const std::string	enemyFireAudioPath = game->get(ConfigType::GAME, "sounds.enemyFire").template get<std::string>();
	const std::string	rocketFireAudioPath = game->get(ConfigType::GAME, "sounds.rocketFire").template get<std::string>();
	
	Sound	enemyFire = LoadSound(enemyFireAudioPath.c_str());
	Sound	rocketFire = LoadSound(rocketFireAudioPath.c_str());

	_sounds.resize(2);
	_sounds[0] = enemyFire;
	_sounds[1] = rocketFire;

	_speedXDirection = 1.0f;
	_locationYOffset = 0.0f;
}

GameScene::~GameScene()
{
	for (Sound &sound : _sounds)
	{
		UnloadSound(sound);
	}
	CloseAudioDevice();

	for (ACharacter *monster : _monsters)
	{
		delete monster;
	}

	delete _player;
}

void	GameScene::eventHandler(void)
{
	_playerStep = 0.0f;
	if (IsKeyDown(KEY_RIGHT)) _playerStep += 2.0f;
	if (IsKeyDown(KEY_LEFT)) _playerStep -= 2.0f;
	if (IsKeyPressed(KEY_ENTER)) PlaySound(_sounds[0]);
	if (IsKeyPressed(KEY_SPACE)) PlaySound(_sounds[1]);
}

void	GameScene::drawingHandler(void)
{
	bool	anyMonsterHitsWall = false;
	bool	anyMonsterHitsFloor = false;
	for (ACharacter *monster : _monsters)
	{
		if (!monster->getIsAlive())
		{
			continue ;
		}
		float	speedX = monster->getSpeed();
		monster->adjustLocation(speedX * _speedXDirection, _locationYOffset, _enemyBoundaries);
		DrawTexturePro(_texture, monster->getSrcTile(), monster->getDestTile(), {0.0f, 0.0f}, 0.0f, WHITE);
		if (monster->checkHitWall(_enemyBoundaries))
		{
			anyMonsterHitsWall = true;
		}
		if (monster->checkHitFloor(_enemyBoundaries))
		{
			anyMonsterHitsFloor = true;
		}
	}
	if (anyMonsterHitsWall)
	{
		_speedXDirection *= -1;
		_locationYOffset = _cellHeigth;
	}
	else
	{
		_locationYOffset = 0.0f;
	}
	float speedX = _player->getSpeed();
	_player->adjustLocation(_playerStep * speedX, 0.0f, _playerBoundaries);
	DrawTexturePro(_texture, _player->getSrcTile(), _player->getDestTile(), {0.0f, 0.0f}, 0.0f, WHITE);
	_player->checkHitWall(_playerBoundaries);
	if (anyMonsterHitsFloor)
	{
		DrawText("Game Over!", 0, 0, 20, BLACK);
	}
}

