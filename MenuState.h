#pragma once

#include "pch.h"


class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	virtual void Draw() override;
	virtual bool Update(sf::Time dt) override;
	virtual bool HandleEvent(const sf::Event& ev) override;


private:


private:
	sf::Sprite m_Background;
	GUI::Container m_GUIContainer;
};