#include "pch.h"
#include "TextNode.h"

TextNode::TextNode(const FontHandles & fonts, const std::string & text,int size):m_Text(text,fonts.Get(Fonts::Main),size)
{
}

void TextNode::SetString(const std::string & text)
{
	m_Text.setString(text);
	sf::FloatRect bounds = m_Text.getLocalBounds();
	m_Text.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
}

void TextNode::DrawThis(sf::RenderTarget & rt, sf::RenderStates rs) const
{
	rt.draw(m_Text, rs);
}

