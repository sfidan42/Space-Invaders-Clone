#include <raylib.h>
#include "GameInstance.hpp"

using json = nlohmann::json;

int	main(void)
{
	GameInstance	*game = GameInstance::getInstance();

	game->setGame("configs/GameConfig.json");
	game->setLevel("configs/Level1.json");

	InitWindow(800, 600, "Space Invaders Clone");

	SetTargetFPS(120);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText(game->get(ConfigType::GAME, "window.height").dump().c_str(), 5, 10, 20, LIGHTGRAY);

		EndDrawing();
	}

	CloseWindow();

	return (0);
}
