#include "pch.h"

GameState::GameState(StateStack & stack, Context context):State(stack,context),m_World(*context.window,*context.fonts),m_Player(*context.player)
{
}

void GameState::Draw()
{
	m_World.Draw();
}

bool GameState::Update(sf::Time dt)
{
	m_World.Update(dt);

	CommandQueue& queue = m_World.GetCmdQueue();
	m_Player.HandleRealTimeInput(queue);

	return true;
}

bool GameState::HandleEvent(const sf::Event & event)
{
	// Game input handling
	CommandQueue& queue = m_World.GetCmdQueue();
	m_Player.HandleEvent(event, queue);
	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		RequestStackPush(States::Pause);

	return true;
}
