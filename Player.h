#pragma once
#include "pch.h"


class Player
{
public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		ActionCount
	};
public:

	Player();
	void HandleEvent(const sf::Event& ev, CommandQueue& cmdQueue);
	void HandleRealTimeInput(CommandQueue& cmdQueue);

	void AsignKey(Action ac, sf::Keyboard::Key k);
	sf::Keyboard::Key GetAssignKey(Action ac);

private:
	bool isRealTimeInput(Action ac);
private:
	std::map<sf::Keyboard::Key, Action> m_KeyBinding;
	std::map<Action, Command> m_ActionBinding;
};