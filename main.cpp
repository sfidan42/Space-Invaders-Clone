#include <raylib.h>
#include "GameInstance.hpp"
#include "Scene.hpp"
#include "GameScene.hpp"

int	main(void)
{
	GameInstance	*game = GameInstance::getInstance();
	std::vector<Scene *>	scenes(3);

	game->setGame("configs/GameConfig.json");
	game->setLevel("configs/Level1.json");

	const unsigned int	screenW = game->get(ConfigType::GAME, "windows.main.width").template get<const unsigned int>();
	const unsigned int	screenH = game->get(ConfigType::GAME, "windows.main.height").template get<const unsigned int>();

	InitWindow(screenW, screenH, "Space Invaders Clone");

	//const int	fontSize = game->get(ConfigType::GAME, "fontsize").template get<const int>();

	const int	fps = game->get(ConfigType::GAME, "fps").template get<const int>();
	SetTargetFPS(fps);

	scenes[0] = new GameScene();

	while (!WindowShouldClose())
	{
		scenes[0]->eventHandler();

		BeginDrawing();
		ClearBackground(RAYWHITE);

		scenes[0]->drawingHandler();

		EndDrawing();
	}

	CloseWindow();

	return (0);
}
