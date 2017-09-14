#include "pch.h"
#include "SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture & textures):m_Sprite(textures)
{
}

SpriteNode::SpriteNode(const sf::Texture & textures, sf::IntRect rect):m_Sprite(textures,rect)
{
}

void SpriteNode::DrawThis(sf::RenderTarget & target, sf::RenderStates states)const
{
	target.draw(m_Sprite,states);
}
