#pragma once
#include "pch.h"

class TitleState : public State
{
public:
	TitleState(StateStack& stack,
		Context context);
	virtual void Draw();
	virtual bool Update(sf::Time dt);
	virtual bool HandleEvent(const sf::Event& event);
private:
	sf::Sprite m_BackgroundSprite;
	sf::Text m_Text;
	bool m_ShowText;
	sf::Time m_TextEffectTime;
};