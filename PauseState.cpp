#include "pch.h"
#include "PauseState.h"

PauseState::PauseState(StateStack & stack, Context context):State(stack,context)
{
	sf::Font& font = context.fonts->Get(Fonts::Main);
	sf::Vector2f viewSize = context.window->getView().getSize();

	m_PauseText.setFont(font);
	m_PauseText.setString("Game Paused");
	m_PauseText.setCharacterSize(70);
	sf::FloatRect bounds = m_PauseText.getLocalBounds();
	m_PauseText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	m_PauseText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	m_InstructionText.setFont(font);
	m_InstructionText.setString("(Press Backspace to return to the main menu)");
	 bounds = m_InstructionText.getLocalBounds();
	m_InstructionText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	m_InstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(m_PauseText);
	window.draw(m_InstructionText);
}

bool PauseState::Update(sf::Time dt)
{
	return false;
}

bool PauseState::HandleEvent(const sf::Event & ev)
{
	if (ev.type != sf::Event::KeyPressed)
		return false;

	if (ev.key.code == sf::Keyboard::Escape)
	{
		// Escape pressed, remove itself to return to the game
		RequestStackPop();
	}

	if (ev.key.code == sf::Keyboard::BackSpace)
	{
		// Escape pressed, remove itself to return to the game
		RequestStackClear();
		RequestStackPush(States::Menu);
	}
	return false;
}
