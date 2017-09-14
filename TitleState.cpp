#include "pch.h"
#include "TitleState.h"

TitleState::TitleState(StateStack & stack, Context context):State(stack,context),m_ShowText(true),m_TextEffectTime(sf::Time::Zero)
{
	m_BackgroundSprite.setTexture(context.textures->Get(Textures::TitleScreen));
	m_Text.setFont(context.fonts->Get(Fonts::Main));
	m_Text.setString("Press any key to start");
	sf::FloatRect bounds = m_Text.getLocalBounds();
	m_Text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	m_Text.setPosition(context.window->getView().getSize() / 2.0f);

}

void TitleState::Draw()
{
	sf::RenderWindow& rw = *GetContext().window;
	rw.draw(m_BackgroundSprite);
	if (m_ShowText) rw.draw(m_Text);
}

bool TitleState::Update(sf::Time dt)
{
	m_TextEffectTime += dt;
	if (m_TextEffectTime >= sf::seconds(0.5f))
	{
		m_ShowText = !m_ShowText;
		m_TextEffectTime = sf::Time::Zero;
	}
	
	return true;
}

bool TitleState::HandleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		RequestStackPop();
		RequestStackPush(States::Menu);
	}
	return  true;
}
