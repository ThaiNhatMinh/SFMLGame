#pragma once

#include "pch.h"

#include "State.h"
class StateStack : public sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};

public:
	explicit StateStack(State::Context context);

	template <typename T>
	void			RegisterState(States::ID stateID);
	void			Draw();
	void			Update(sf::Time dt);
	void			HandleEvent(const sf::Event& ev);

	void			PushState(States::ID stateID);
	void			PopState();
	void			ClearState();

	bool			IsEmpty()const;

private:
	State::Ptr		CreateState(States::ID stateID);
	void			ApplyPendingChanges();

private:
	struct PendingChange
	{
		Action action;
		States::ID stateID;
		explicit PendingChange(Action ac, States::ID id = States::None) :action(ac), stateID(id) {}
	};

private:
	std::vector<State::Ptr> m_Stack;
	std::vector<PendingChange> m_PendingList;
	State::Context m_Context;
	std::map<States::ID, std::function<State::Ptr()>> m_Factories;

};

template<typename T>
inline void StateStack::RegisterState(States::ID stateID)
{
	m_Factories[stateID] = [this]() {
		return State::Ptr(new T(*this, m_Context)); };
}
