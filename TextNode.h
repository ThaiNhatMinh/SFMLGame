#pragma once

#include "pch.h"


class TextNode :public SceneNode
{
public:
	explicit TextNode(const FontHandles& fonts, const std::string& text,int size = 20);
	void SetString(const std::string& text);

private:
	void DrawThis(sf::RenderTarget& rt, sf::RenderStates rs)const;

private:
	sf::Text m_Text;
};