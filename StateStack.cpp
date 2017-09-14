#include "pch.h"

State::Ptr StateStack::CreateState(States::ID stateID)
{
	std::map<States::ID, std::function<State::Ptr()>>::iterator found = m_Factories.find(stateID);
	assert(found != m_Factories.end());
	return found->second();
}

void StateStack::ApplyPendingChanges()
{
	for (auto itr = m_PendingList.begin(); itr != m_PendingList.end(); itr++)
	{
		switch (itr->action)
		{
		case Push:
			m_Stack.push_back(CreateState(itr->stateID)); break;
		case Pop:
			m_Stack.pop_back(); break;
		case Clear:
			m_Stack.clear(); break;
		}
	}
	m_PendingList.clear();
}

StateStack::StateStack(State::Context context) :m_Context(context)
{
}

void StateStack::Draw()
{
	for (auto itr = m_Stack.begin(); itr != m_Stack.end(); itr++)
		(*itr)->Draw();
}

void StateStack::Update(sf::Time dt)
{
	for (auto itr = m_Stack.rbegin(); itr != m_Stack.rend(); itr++)
		if (!(*itr)->Update(dt)) break;

	ApplyPendingChanges();
}

void StateStack::HandleEvent(const sf::Event & ev)
{
	for (auto itr = m_Stack.rbegin(); itr != m_Stack.rend(); itr++)
		if (!(*itr)->HandleEvent(ev)) return;

	ApplyPendingChanges();
}

void StateStack::PushState(States::ID stateID)
{
	m_PendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::PopState()
{
	m_PendingList.push_back(PendingChange(Pop));
}

void StateStack::ClearState()
{
	m_PendingList.push_back(PendingChange(Clear));
}

bool StateStack::IsEmpty() const
{
	return m_Stack.empty();
}
