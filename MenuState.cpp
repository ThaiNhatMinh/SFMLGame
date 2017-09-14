#include "pch.h"
#include "MenuState.h"

MenuState::MenuState(StateStack& stack, Context context):State(stack,context)
{
	sf::Texture& tex = context.textures->Get(Textures::TitleScreen);
	sf::Font& font = context.fonts->Get(Fonts::Main);

	m_Background.setTexture(tex);

	//sf::Text play;
	//play.setFont(font);
	//play.setString("Play");
	//sf::FloatRect bounds = play.getLocalBounds();
	//play.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	//play.setPosition(context.window->getView().getSize() / 2.0f);
	//m_Options.push_back(play);
	auto playButton = std::make_shared<GUI::Button>(*context.textures, *context.fonts);
	playButton->setPosition(100, 250);
	playButton->SetText("Play");
	playButton->SetCallback([this]()
	{
		RequestStackPop();
		RequestStackPush(States::Game);
	});

	auto settingsButton = std::make_shared<GUI::Button>(*context.textures, *context.fonts);
	settingsButton->setPosition(100, 300);
	settingsButton->SetText("Settings");
	settingsButton->SetCallback([this]()
	{
		RequestStackPush(States::Settings);
	});

	auto exitButton = std::make_shared<GUI::Button>(*context.textures, *context.fonts);
	exitButton->setPosition(100, 350);
	exitButton->SetText("Exit");
	exitButton->SetCallback([this]()
	{
		RequestStackPop();
	});

	m_GUIContainer.Pack(playButton);
	m_GUIContainer.Pack(settingsButton);
	m_GUIContainer.Pack(exitButton);
	
}

void MenuState::Draw()
{
	sf::RenderWindow& rw = *GetContext().window;

	rw.setView(rw.getDefaultView());
	rw.draw(m_Background);
	rw.draw(m_GUIContainer);
}

bool MenuState::Update(sf::Time dt)
{
	return true;
}

bool MenuState::HandleEvent(const sf::Event & ev)
{
	m_GUIContainer.HandleEvent(ev);
	return false;

}

