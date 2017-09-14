#include "pch.h"
#include "Application.h"
#include "Texture.h"
#include "ResourceHandle.h"
#include <sstream>
const sf::Time Appicaltion::TimePerFrame = sf::seconds(1.0f / 60.0f);


Appicaltion::Appicaltion():m_Window(sf::VideoMode(800,600),"Game",sf::Style::Close),m_Textures(),m_Fonts(),m_Player(),m_StateStack(State::Context(m_Window,m_Textures,m_Fonts,m_Player))
{
	m_Window.setKeyRepeatEnabled(false);
	m_Fonts.Load(Fonts::Main, "Media/Sansation.ttf");
	m_Textures.Load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");
	m_Textures.Load(Textures::ButtonNormal, "Media/Textures/ButtonNormal.png");
	m_Textures.Load(Textures::ButtonSelected, "Media/Textures/ButtonSelected.png");
	m_Textures.Load(Textures::ButtonPressed, "Media/Textures/ButtonPressed.png");

	m_StatisticsText.setFont(m_Fonts.Get(Fonts::Main));
	m_StatisticsText.setPosition(5.f, 5.f);
	m_StatisticsText.setCharacterSize(10u);

	RegisterState();
	m_StateStack.PushState(States::Title);
}

void Appicaltion::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_Window.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;

		//while (timeSinceLastUpdate > TimePerFrame)
		{
		//	timeSinceLastUpdate -= TimePerFrame;

			ProcessInput();
			Update(dt);
			// Check inside this loop, because stack might be empty before update() call
			if (m_StateStack.IsEmpty())
				m_Window.close();
		}

		UpdateStatistics(dt);
		Render();
	}
}

void Appicaltion::RegisterState()
{
	m_StateStack.RegisterState<TitleState>(States::Title);
	m_StateStack.RegisterState<MenuState>(States::Menu);
	m_StateStack.RegisterState<GameState>(States::Game);
	m_StateStack.RegisterState<PauseState>(States::Pause);
	m_StateStack.RegisterState<SettingState>(States::Settings);
}

void Appicaltion::ProcessInput()
{
	sf::Event ev;
	while (m_Window.pollEvent(ev))
	{
		m_StateStack.HandleEvent(ev);
		if (ev.type = sf::Event::Closed)
			m_Window.close();
	}
}

void Appicaltion::Update(sf::Time dt)
{
	m_StateStack.Update(dt);
}

void Appicaltion::UpdateStatistics(sf::Time dt)
{
	m_StatisticsUpdateTime += dt;
	m_StatisticsNumFrames += 1;
	if (m_StatisticsUpdateTime >= sf::seconds(1.0f))
	{
		std::stringstream stream;
		stream << m_StatisticsNumFrames;
		 
		m_StatisticsText.setString("FPS: " + stream.str());

		m_StatisticsUpdateTime -= sf::seconds(1.0f);
		m_StatisticsNumFrames = 0;
	}
}

void Appicaltion::Render()
{
	m_Window.clear();

	m_StateStack.Draw();

	m_Window.setView(m_Window.getDefaultView());
	m_Window.draw(m_StatisticsText);

	m_Window.display();
}
