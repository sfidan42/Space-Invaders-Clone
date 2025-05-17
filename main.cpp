#include <raylib.h>
#include "GameInstance.hpp"
#include "PlayerCharacter.hpp"
#include "MonsterCharacter.hpp"
#include "Conversions.hpp"
#include <iostream>

int	main(void)
{
	GameInstance	*game = GameInstance::getInstance();

	game->setGame("configs/GameConfig.json");
	game->setLevel("configs/Level1.json");

	const unsigned int	screenW = game->get(ConfigType::GAME, "windows.main.width").template get<const unsigned int>();
	const unsigned int	screenH = game->get(ConfigType::GAME, "windows.main.height").template get<const unsigned int>();

	InitWindow(screenW, screenH, "Space Invaders Clone");

	//const int	fontSize = game->get(ConfigType::GAME, "fontsize").template get<const int>();

	std::string	texturePath = game->get(ConfigType::GAME, "textures.SpaceInvaders").template get<std::string>();
	Texture2D	texture = LoadTexture(texturePath.c_str());

	const int fps = game->get(ConfigType::GAME, "fps").template get<const int>();
	SetTargetFPS(fps);

	Rectangle	enemyBoundaries = game->get(ConfigType::GAME, "windows.enemies").template get<Rectangle>();
	Rectangle	playerBoundaries = game->get(ConfigType::GAME, "windows.player").template get<Rectangle>();

	enemyBoundaries.x *= screenW;
	enemyBoundaries.y *= screenH;
	enemyBoundaries.width *= screenW;
	enemyBoundaries.height *= screenH;

	playerBoundaries.x *= screenW;
	playerBoundaries.y *= screenH;
	playerBoundaries.width *= screenW;
	playerBoundaries.height *= screenH;

	std::vector<unsigned int>	monsterCounts = game->get(ConfigType::LEVEL, "monsterCounts").template get<std::vector<unsigned int>>();
	std::vector<ACharacter *>	monsters;

	const int	totalNumMonsters = std::accumulate(monsterCounts.begin(), monsterCounts.end(), 0);
	
	monsters.reserve(totalNumMonsters);

	ACharacterDataType	monsterData = game->get(ConfigType::LEVEL, "monster.data").template get<ACharacterDataType>();
	Rectangle			monsterSrcTile = game->get(ConfigType::GAME, "textures.sourceTiles.monster1").template get<Rectangle>();
	float				resizeRatio = game->get(ConfigType::GAME, "textures.resizeRatio").template get<float>();
	Rectangle			monsterDestTile;

	monsterDestTile.width = monsterSrcTile.width * resizeRatio;
	monsterDestTile.height = monsterSrcTile.height * resizeRatio;

	float	cellWidth = 1.5f * monsterDestTile.width;
	float	cellHeight = 1.5f * monsterDestTile.height;

	assert(cellWidth * *std::max_element(monsterCounts.begin(), monsterCounts.end()) <= enemyBoundaries.width);
	assert(cellHeight * monsterCounts.size() <= enemyBoundaries.height);

	for (unsigned int	monsterCountIdx = 0; monsterCountIdx < monsterCounts.size(); monsterCountIdx++)
	{
		unsigned int	monsterCount = monsterCounts[monsterCountIdx];

		for (unsigned int rowCountIdx = 0; rowCountIdx < monsterCount; rowCountIdx++)
		{
			monsterDestTile.x = enemyBoundaries.x + cellWidth * rowCountIdx - monsterDestTile.width / 2;
			monsterDestTile.y = enemyBoundaries.y + cellHeight * monsterCountIdx - monsterDestTile.height / 2;
			ACharacter	*monster = new MonsterCharacter(monsterDestTile, monsterData);
			monsters.push_back(monster);
		}
	}

	ACharacterDataType	playerData = game->get(ConfigType::LEVEL, "player.data").template get<ACharacterDataType>();
	Rectangle			playerSrcTile = game->get(ConfigType::GAME, "textures.sourceTiles.rocket1").template get<Rectangle>();
	Rectangle			playerDestTile;

	json	playerLocation = game->get(ConfigType::LEVEL, "player.location");
	playerDestTile.x = playerLocation["horizontal"].template get<float>();
	playerDestTile.y = playerLocation["vertical"].template get<float>();
	playerDestTile.width = playerSrcTile.width * resizeRatio;
	playerDestTile.height = playerSrcTile.height * resizeRatio;

	playerDestTile.x *= screenW;
	playerDestTile.y *= screenH;
	playerDestTile.x -= playerDestTile.width / 2;
	playerDestTile.y -= playerDestTile.height / 2;

	ACharacter	*player = new PlayerCharacter(playerDestTile, playerData);

	const std::string	enemyFireAudioPath = game->get(ConfigType::GAME, "sounds.enemyFire").template get<std::string>();
	const std::string	rocketFireAudioPath = game->get(ConfigType::GAME, "sounds.rocketFire").template get<std::string>();

	InitAudioDevice();

	Sound	enemyFire = LoadSound(enemyFireAudioPath.c_str());
	Sound	rocketFire = LoadSound(rocketFireAudioPath.c_str());
	
	Vector2	origin = { 0, 0 };

	float	speedXDirection = 1.0f;

	while (!WindowShouldClose())
	{
		float	playerStep = 0.0f;
		if (IsKeyDown(KEY_RIGHT)) playerStep += 2.0f;
        if (IsKeyDown(KEY_LEFT)) playerStep -= 2.0f;
		if (IsKeyPressed(KEY_SPACE)) PlaySound(rocketFire);
		if (IsKeyPressed(KEY_ENTER)) PlaySound(enemyFire);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		bool	anyMonsterHitsWall = false;
		for (ACharacter *monster : monsters)
		{
			float	speedX = monster->getSpeed() * speedXDirection;
			monster->adjustLocation(speedX, 0.0f, enemyBoundaries);
			DrawTexturePro(texture, monsterSrcTile, monster->getDestTile(), origin, 0.0f, WHITE);
			if (monster->checkHitWall(enemyBoundaries))
			{
				anyMonsterHitsWall = true;
			}
		}
		if (anyMonsterHitsWall)
		{
			speedXDirection *= -1;
			
		}
		float speedX = player->getSpeed();
		player->adjustLocation(playerStep * speedX, 0.0f, playerBoundaries);
		DrawTexturePro(texture, playerSrcTile, player->getDestTile(), origin, 0.0f, WHITE);
		player->checkHitWall(playerBoundaries);
		EndDrawing();
	}

	UnloadTexture(texture);
	UnloadSound(rocketFire);
	UnloadSound(enemyFire);
	
	CloseAudioDevice();
	CloseWindow();

	for (ACharacter *monster : monsters)
	{
		delete monster;
	}
	delete player;

	return (0);
}
