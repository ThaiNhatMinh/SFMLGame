#pragma once
#include "pch.h"
#include <functional>
#include <cassert>
namespace Category
{
	enum Type
	{
		None = 0,
		Scene = 1 << 0,
		PlayerAircraft = 1 << 1,
		AlliedAircraft = 1 << 2,
		EnemyAircraft = 1 << 3,
	};
}

class SceneNode;
struct Command
{
	std::function<void(SceneNode&, sf::Time)>	action;
	unsigned int								category;
};