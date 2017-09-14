#include "pch.h"

struct  AircraftMover
{
	sf::Vector2f velocity;
	AircraftMover(float x, float y) :velocity(x, y) {}
	void operator()(Aircraft& node, sf::Time )const
	{
		node.Accelerate(velocity);
	}
	
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> DerivedAction(Function fn)
{
	return [=](SceneNode& node, sf::Time dt)
	{
		assert(dynamic_cast<GameObject*>(&node) != nullptr);
		fn(static_cast<GameObject&>(node), dt); 
	};

}
Player::Player()
{
	// Set initial key bindings
	m_KeyBinding[sf::Keyboard::Left] = MoveLeft;
	m_KeyBinding[sf::Keyboard::Right] = MoveRight;
	m_KeyBinding[sf::Keyboard::Up] = MoveUp;
	m_KeyBinding[sf::Keyboard::Down] = MoveDown;

	// Set initial command
	const float playerSpeed = 200.f;

	m_ActionBinding[MoveLeft].action = DerivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	m_ActionBinding[MoveRight].action = DerivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
	m_ActionBinding[MoveUp].action = DerivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
	m_ActionBinding[MoveDown].action = DerivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
	for (auto& pair : m_ActionBinding)
		pair.second.category = Category::PlayerAircraft;

}
void Player::HandleEvent(const sf::Event & ev, CommandQueue & cmdQueue)
{
	if (ev.type == sf::Event::KeyPressed)
	{
		auto found = m_KeyBinding.find(ev.key.code);
		if (found != m_KeyBinding.end() && !isRealTimeInput(found->second))
			cmdQueue.Push(m_ActionBinding[found->second]);
	}
}

void Player::HandleRealTimeInput(CommandQueue & cmdQueue)
{
	for (auto& pair : m_KeyBinding)
	{
		bool a = sf::Keyboard::isKeyPressed(pair.first);
		bool b = isRealTimeInput(pair.second);
		if (a && b )
			cmdQueue.Push(m_ActionBinding[pair.second]);
	}
}

void Player::AsignKey(Action ac, sf::Keyboard::Key k)
{
	// Remove all keys that already map to action
	for (auto itr = m_KeyBinding.begin(); itr != m_KeyBinding.end();)
		if (itr->second == ac) 
			m_KeyBinding.erase(itr++);
		else itr++;

	m_KeyBinding[k] = ac;
}

sf::Keyboard::Key Player::GetAssignKey(Action ac)
{
	for (auto& pair : m_KeyBinding)
		if (pair.second == ac) return pair.first;

	return sf::Keyboard::Unknown;
}

bool Player::isRealTimeInput(Action ac)
{
	switch (ac)
	{
	case Player::MoveLeft:
	case Player::MoveRight:
	case Player::MoveUp:
	case Player::MoveDown:
		return true;
	default:
		return false;
	}
}
