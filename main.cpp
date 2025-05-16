#include <raylib.h>
#include "GameInstance.hpp"

int	main(void)
{
	GameInstance	*game = GameInstance::getInstance();

	game->setGame("configs/GameConfig.json");
	game->setLevel("configs/Level1.json");

	const int	screenW = game->get(ConfigType::GAME, "window.width").template get<const int>();
	const int	screenH = game->get(ConfigType::GAME, "window.height").template get<const int>();

	InitWindow(screenW, screenH, "Space Invaders Clone");

	const float	marginV = game->get(ConfigType::GAME, "margin.vertical").template get<const float>();
	const float	marginH = game->get(ConfigType::GAME, "margin.horizontal").template get<const float>();
	const int	gapV = screenW * marginV;
	const int	gapH = screenH * marginH;
	const int	fontSize = game->get(ConfigType::GAME, "fontsize").template get<const int>();

	std::string	texturePath = game->get(ConfigType::GAME, "textures.SpaceInvaders").template get<std::string>();
	Texture2D	texture = LoadTexture(texturePath.c_str());

	const int fps = game->get(ConfigType::GAME, "fps").template get<const int>();
	SetTargetFPS(fps);

	Rectangle	monsterSource = { 100, 3200, 400, 300 };
	Rectangle	monsterDestination = { 100, 100, 80, 60 };
	Vector2		monsterOrigin = { 0, 0 };
	Color		monsterTint = { 0xFF, 0xFF, 0xFF, 0xFF };

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText("Let's play the game!", gapV, gapH, fontSize, LIGHTGRAY);
		//DrawTexture(texture, screenW / 2 - texture.width / 2, screenH / 2 - texture.height / 2, WHITE);
		DrawTexturePro(texture, monsterSource, monsterDestination, monsterOrigin, 0.0f, monsterTint);
		//DrawTextureNPatch(texture, )
		EndDrawing();
	}

	UnloadTexture(texture);
	CloseWindow();

	return (0);
}
