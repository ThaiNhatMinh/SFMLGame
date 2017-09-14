#include "pch.h"
#include "Button.h"

GUI::Button::Button(const TextureHandles & textures, const FontHandles & fonts):m_Callback(), m_NormalTex(textures.Get(Textures::ButtonNormal)), m_SelectTex(textures.Get(Textures::ButtonSelected)), m_PressTex(textures.Get(Textures::ButtonPressed))
	, m_Sprite()
	, m_Text("", fonts.Get(Fonts::Main), 16)
	, m_IsToggle(false)
{
	m_Sprite.setTexture(m_NormalTex);
	sf::FloatRect bounds = m_Sprite.getLocalBounds();
	m_Text.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

bool GUI::Button::IsSelectable() const
{
	return true;
}

void GUI::Button::Select()
{
	Component::Select();
	m_Sprite.setTexture(m_SelectTex);
}

void GUI::Button::DeSelect()
{
	Component::DeSelect();
	m_Sprite.setTexture(m_NormalTex);
}

void GUI::Button::Active()
{
	Component::Active();
	if (m_IsToggle) m_Sprite.setTexture(m_PressTex);
	if (m_Callback) m_Callback();
	if (!m_IsToggle) DeActive();

}

void GUI::Button::DeActive()
{
	Component::DeActive();
	if (m_IsToggle)
	{
		if (IsSelect())
			m_Sprite.setTexture(m_SelectTex);
		else m_Sprite.setTexture(m_NormalTex);
	}
}

void GUI::Button::HandleEvent(const sf::Event & ev)
{
}

void GUI::Button::SetCallback(Callback callback)
{
	m_Callback = callback;
}

void GUI::Button::SetText(const std::string & text)
{
	m_Text.setString(text);
}

void GUI::Button::SetToggle(bool flag)
{
	m_IsToggle = flag;
}

void GUI::Button::draw(sf::RenderTarget & rt, sf::RenderStates rs) const
{
	rs.transform *= getTransform();
	rt.draw(m_Sprite, rs);
	rt.draw(m_Text, rs);
}
