#include "pch.h"
#include "SettingState.h"

SettingState::SettingState(StateStack & stack, Context context):State(stack,context)
{
	m_BackBround.setTexture(context.textures->Get(Textures::TitleScreen));

	AddButtonLabel(Player::MoveDown, 300.0f, "Move Down", context);
	AddButtonLabel(Player::MoveUp, 250.0f, "Move Up", context);
	AddButtonLabel(Player::MoveLeft, 150.0f, "Move Left", context);
	AddButtonLabel(Player::MoveRight, 200.0f, "Move Right", context);

	UpdateLabel();
	auto backButton = std::make_shared<GUI::Button>(*context.textures, *context.fonts);
	backButton->setPosition(80.f, 375.f);
	backButton->SetText("Back");
	backButton->SetCallback(std::bind(&SettingState::RequestStackPop, this));

	m_GUIContainer.Pack(backButton);
}

void SettingState::Draw()
{
	sf::RenderWindow& rw = *GetContext().window;
	rw.draw(m_BackBround);
	rw.draw(m_GUIContainer);

}

bool SettingState::Update(sf::Time dt)
{
	return 1;
}

bool SettingState::HandleEvent(const sf::Event & ev)
{
	bool isKeyBinding = false;
	for (std::size_t i = 0; i < Player::ActionCount; i++)
	{
		if (m_BindingButton[i]->IsActive())
		{
			isKeyBinding = true;
			if (ev.type == sf::Event::KeyReleased)
			{
				GetContext().player->AsignKey(static_cast<Player::Action>(i), ev.key.code);
				m_BindingButton[i]->DeActive();
			}
			break;
		}
	}

	// If pressed button changed key bindings, update labels; otherwise consider other buttons in container
	if (isKeyBinding)
		UpdateLabel();
	else
		m_GUIContainer.HandleEvent(ev);

	return false;
}

void SettingState::UpdateLabel()
{
	Player& player = *GetContext().player;

	for (std::size_t i = 0; i < Player::ActionCount; ++i)
	{
		sf::Keyboard::Key key = player.GetAssignKey(static_cast<Player::Action>(i));
		m_BindingLabel[i]->SetText(toString(key));
	}
}

void SettingState::AddButtonLabel(Player::Action ac, float y, const std::string & text, Context context)
{
	m_BindingButton[ac] = std::make_shared<GUI::Button>(*context.textures, *context.fonts);
	m_BindingButton[ac]->setPosition(80.f, y);
	m_BindingButton[ac]->SetText(text);
	m_BindingButton[ac]->SetToggle(true);

	m_BindingLabel[ac] = std::make_shared<GUI::Label>("", *context.fonts);
	m_BindingLabel[ac]->setPosition(300.f, y + 15.f);

	m_GUIContainer.Pack(m_BindingButton[ac]);
	m_GUIContainer.Pack(m_BindingLabel[ac]);
}
