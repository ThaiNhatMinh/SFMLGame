#pragma once
#include "pch.h"

class GameState :public State
{
public:
	GameState(StateStack& stack,
		Context context);
	virtual void Draw();
	virtual bool Update(sf::Time dt);
	virtual bool HandleEvent(const sf::Event& event);
private:
	World m_World;
	Player& m_Player;
};