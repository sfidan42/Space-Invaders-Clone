#include <raylib.h>
#include "GameInstance.hpp"

using json = nlohmann::json;

int	main(void)
{
	GameInstance	*game = GameInstance::getInstance();

	game->setGame("configs/GameConfig.json");
	game->setLevel("configs/Level1.json");

	const int	windowW = game->get(ConfigType::GAME, "window.width").template get<const int>();
	const int	windowH = game->get(ConfigType::GAME, "window.height").template get<const int>();
	InitWindow(windowW, windowH, "Space Invaders Clone");

	const int fps = game->get(ConfigType::GAME, "fps").template get<const int>();
	SetTargetFPS(fps);

	const float	marginH = game->get(ConfigType::GAME, "margin.horizontal").template get<const float>();
	const float	marginV = game->get(ConfigType::GAME, "margin.vertical").template get<const float>();

	const int	gapH = windowH * marginH;
	const int	gapV = windowW * marginV;

	const int	fontSize = game->get(ConfigType::GAME, "fontsize").template get<const int>();

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText(game->get(ConfigType::GAME).dump().c_str(), gapV, gapH, fontSize, LIGHTGRAY);
		DrawText(game->get(ConfigType::LEVEL).dump().c_str(), gapV, windowH / 2, fontSize, LIGHTGRAY);

		EndDrawing();
	}

	CloseWindow();

	return (0);
}
