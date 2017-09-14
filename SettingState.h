#pragma once
#include "pch.h"

class SettingState :public State
{
public:
	SettingState(StateStack& stack, Context context);

	void Draw()override;
	bool Update(sf::Time dt) override;
	bool HandleEvent(const sf::Event& ev) override;
private:
	void UpdateLabel();
	void AddButtonLabel(Player::Action ac, float y, const std::string& text, Context context);
private:
	GUI::Container m_GUIContainer;
	sf::Sprite m_BackBround;

	std::array<GUI::Button::Ptr, Player::ActionCount> m_BindingButton;
	std::array<GUI::Label::Ptr, Player::ActionCount> m_BindingLabel;
};