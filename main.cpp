#include <raylib.h>
#include "GameInstance.hpp"
#include "PlayerCharacter.hpp"
#include "MonsterCharacter.hpp"
#include "Conversions.hpp"

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

	std::vector<unsigned int>	monsterCounts = game->get(ConfigType::LEVEL, "monsterCounts").template get<std::vector<unsigned int>>();
	std::vector<float>	rowSpeedMultipliers = game->get(ConfigType::LEVEL, "rowSpeedMultipliers").template get<std::vector<float>>();

	assert(monsterCounts.size() == rowSpeedMultipliers.size());

	std::vector<ACharacter *>	monsters;

	const int	totalNumMonsters = std::accumulate(monsterCounts.begin(), monsterCounts.end(), 0);
	
	monsters.reserve(totalNumMonsters);

	ACharacterDataType	monsterData = game->get(ConfigType::LEVEL, "monster.data").template get<ACharacterDataType>();
	Rectangle			monsterSrcTile = game->get(ConfigType::GAME, "textures.sourceTiles.monster1").template get<Rectangle>();
	float				resizeRatio = game->get(ConfigType::GAME, "textures.resizeRatio").template get<float>();
	Rectangle			monsterDestTile;

	monsterDestTile.width = monsterSrcTile.width * resizeRatio;
	monsterDestTile.height = monsterSrcTile.height * resizeRatio;

	float	cellHeight = screenH / (float)monsterCounts.size();
	for (unsigned int	monsterCountIdx = 0; monsterCountIdx < monsterCounts.size(); monsterCountIdx++)
	{
		unsigned int	monsterCount = monsterCounts[monsterCountIdx];

		float	cellWidth = screenW / (float)monsterCount;
		for (unsigned int rowCountIdx = 0; rowCountIdx < monsterCount; rowCountIdx++)
		{
			monsterDestTile.x = cellWidth * rowCountIdx;
			monsterDestTile.y = cellHeight * monsterCountIdx;
			ACharacter	*monster = new MonsterCharacter(monsterDestTile, monsterData);
			monster->adjustSpeed(rowSpeedMultipliers[monsterCountIdx]);
			monsters.push_back(monster);
		}
	}

	ACharacterDataType	playerData = game->get(ConfigType::LEVEL, "player.data").template get<ACharacterDataType>();
	Rectangle			playerSrcTile = game->get(ConfigType::GAME, "textures.sourceTiles.rocket1").template get<Rectangle>();
	Rectangle			playerDestTile;

	json	playerLocation = game->get(ConfigType::LEVEL, "player.location");
	playerDestTile.x = playerLocation["horizontal"].template get<float>();
	playerDestTile.y = playerLocation["vertical"].template get<float>();
	playerDestTile.width = playerSrcTile.width;
	playerDestTile.height = playerSrcTile.height;

	playerDestTile.x *= screenW;
	playerDestTile.y *= screenH;
	playerDestTile.width *= resizeRatio;
	playerDestTile.height *= resizeRatio;

	ACharacter	*player = new PlayerCharacter(playerDestTile, playerData);

	Vector2	origin = { 0, 0 };

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

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		for (ACharacter *monster : monsters)
		{
			float	speedX = monster->getSpeed();
			monster->adjustLocation(speedX, 0.0f, enemyBoundaries);
			DrawTexturePro(texture, monsterSrcTile, monster->getDestTile(), origin, 0.0f, WHITE);
			monster->checkHitWall(enemyBoundaries);
		}
		float speedX = player->getSpeed();
		player->adjustLocation(speedX, 0.0f, playerBoundaries);
		DrawTexturePro(texture, playerSrcTile, player->getDestTile(), origin, 0.0f, WHITE);
		player->checkHitWall(playerBoundaries);
		EndDrawing();
	}

	UnloadTexture(texture);
	CloseWindow();

	for (ACharacter *monster : monsters)
	{
		delete monster;
	}
	delete player;

	return (0);
}
