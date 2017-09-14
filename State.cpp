#include "pch.h"

State::Context::Context(sf::RenderWindow & window, TextureHandles & textures, FontHandles & fonts, Player & player):window(&window),textures(&textures),fonts(&fonts),player(&player)
{
}

State::State(StateStack & st, Context & context):m_pStack(&st),m_Contex(context)
{
}

State::~State()
{
}

void State::RequestStackPush(States::ID stateID)
{
	m_pStack->PushState(stateID);
}

void State::RequestStackPop()
{
	m_pStack->PopState();
}

void State::RequestStackClear()
{
	m_pStack->ClearState();
}

State::Context State::GetContext() const
{
	return m_Contex;
}
