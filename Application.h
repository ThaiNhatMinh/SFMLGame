#pragma once

#include "pch.h"

class Appicaltion : public sf::NonCopyable
{
public:
	Appicaltion();
	void Run();

protected:

	void RegisterState();
	void ProcessInput();
	void Update(sf::Time dt);
	void UpdateStatistics(sf::Time dt);
	void Render();


private:
	static const sf::Time TimePerFrame;

	sf::RenderWindow m_Window;
	TextureHandles m_Textures;
	FontHandles m_Fonts;
	Player m_Player;
	StateStack m_StateStack;

	sf::Text m_StatisticsText;
	sf::Time m_StatisticsUpdateTime;
	std::size_t m_StatisticsNumFrames;
};