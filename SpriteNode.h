#pragma once

#include "pch.h"

class SpriteNode : public SceneNode
{
public:
	explicit SpriteNode(const sf::Texture& textures);
	SpriteNode(const sf::Texture& textures, sf::IntRect rect);

private:
	virtual void DrawThis(sf::RenderTarget & target, sf::RenderStates states)const;
private:
	sf::Sprite m_Sprite;
};