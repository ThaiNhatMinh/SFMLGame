#include "pch.h"
#include "Label.h"

GUI::Label::Label(const std::string & text, const FontHandles & fonts,int size):m_Text(text,fonts.Get(Fonts::Main),size)
{
}

bool GUI::Label::IsSelectable() const
{
	return false;
}

void GUI::Label::HandleEvent(const sf::Event & ev)
{
}

void GUI::Label::SetText(const std::string & text)
{
	m_Text.setString(text);
}

void GUI::Label::draw(sf::RenderTarget & rt, sf::RenderStates rs)const
{
	rs.transform *= getTransform();

	rt.draw(m_Text,rs);
}
