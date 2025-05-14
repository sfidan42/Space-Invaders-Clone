#include <vector>
#include <iostream>
#include <cstdlib>
#include "MonsterCharacter.hpp"
#include "PlayerCharacter.hpp"

#define EPSILON 1e-7

int	main(void)
{
	std::vector<ACharacter *>	monsters;
	std::vector<unsigned int>	monsterCounts;
	PlayerCharacter				player({25.0f, 70.0f}, 100.0f, 100.0f, 50.0f, 7.0f);
	const float					rowWidth = 50.0f;
	const float					columnWidth = 30.0f;

	monsterCounts.push_back(5);
	monsterCounts.push_back(10);
	monsterCounts.push_back(7);
	monsterCounts.push_back(5);
	monsterCounts.push_back(5);

	for (unsigned int monsterCountIdx = 0; monsterCountIdx < monsterCounts.size(); monsterCountIdx++)
	{
		unsigned int	monsterCount = monsterCounts[monsterCountIdx];

		for (unsigned int i = 0; i < monsterCount; i++)
		{
			vec2	monsterLocation = {
				.x = rowWidth / (float)monsterCount,
				.y = columnWidth / (float)i
			};
			ACharacter	*monster = new MonsterCharacter(
				monsterLocation,
				50.0f,
				50.0f,
				10.0f,
				1.0f * 3.0f
			);
			monsters.push_back(monster);
		}
		monsterCountIdx++;
	}

	std::cout << "Allocation for characters completed!" << std::endl;

	while (player.getIsAlive() && !allDead(monsters))
	{
		const int	numOfMonsters = monsters.size();
		int			randomMonsterIdx = rand() % numOfMonsters;

		ACharacter	*monster = monsters[randomMonsterIdx];

		if (std::abs(monster->getLocation().y - player.getLocation().y) < EPSILON)
		{
			player.adjustHealth(0.0f - monster->getDamageValue());
			player.setIsAlive(player.getHealth() <= 0.0f);
		}

		for (ACharacter *monster : monsters)
		{
			monster->adjustLocation({monster->getSpeed(), 0.0f}, {rowWidth, columnWidth});
			float	monsterLocX = monster->getLocation().x;
			if (monsterLocX <= 0 || monsterLocX >= rowWidth)
			{
				monster->setSpeed((-1) * monster->getSpeed());
			}
		}
	}

	for (ACharacter *monster : monsters)
	{
		delete monster;
	}
}
