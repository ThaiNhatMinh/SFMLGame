#pragma once
#include "pch.h"

class PauseState :public State
{

public:
	PauseState(StateStack& stack, Context context);

	virtual void Draw()override;
	virtual bool Update(sf::Time dt)override;
	virtual bool HandleEvent(const sf::Event& ev)override;

private:
	sf::Sprite m_Background;
	sf::Text m_PauseText;
	sf::Text m_InstructionText;
};