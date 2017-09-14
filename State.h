#pragma once
#include "pch.h"
class StateStack;
class State
{
public:
	typedef std::unique_ptr<State>  Ptr;
	struct Context {
		Context(sf::RenderWindow& window,
			TextureHandles& textures,
			FontHandles& fonts,
			Player& player);
		sf::RenderWindow* window;
		TextureHandles* textures;
		FontHandles* fonts;
		Player* player;
	};
public:
	State(StateStack& st, Context& context);
	virtual ~State();

	virtual void Draw() = 0;
	virtual bool Update(sf::Time) = 0;
	virtual bool HandleEvent(const sf::Event&) = 0;

protected:
	void RequestStackPush(States::ID stateID);
	void RequestStackPop();
	void RequestStackClear();
	Context GetContext()const;

private:
	StateStack* m_pStack;
	Context		m_Contex;

};