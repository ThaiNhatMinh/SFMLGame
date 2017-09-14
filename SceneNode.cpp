#include "pch.h"
#include "SceneNode.h"
#include <cassert>

SceneNode::SceneNode():m_pParent(nullptr)
{
}

void SceneNode::AttachChild(Ptr child)
{
	child->m_pParent = this;
	m_Children.push_back(std::move(child));

}

SceneNode::Ptr SceneNode::DetachChild(const SceneNode & node)
{
	auto result = std::find_if(m_Children.begin(), m_Children.end(), [&](Ptr& p) {return p.get() == &node; });
	assert(result != m_Children.end());

	Ptr child = std::move(*result);
	child->m_pParent = nullptr;
	m_Children.erase(result);
	return child;

	
}

void SceneNode::Update(sf::Time dt)
{
	UpdateThis(dt);
	UpdateChildren(dt);
}

sf::Vector2f SceneNode::GetWorldPosition()
{
	return GetWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::GetWorldTransform()
{
	sf::Transform tf = sf::Transform::Identity;
	
	for (const SceneNode* node = this; node != nullptr; node = node->m_pParent)
		tf = node->getTransform() * tf;

	return tf;
}

void SceneNode::OnCommand(const Command & cmd, sf::Time dt)
{
	if (cmd.category & GetCategory())
		cmd.action(*this, dt);

	for (auto& child : m_Children) child->OnCommand(cmd, dt);
}

unsigned int SceneNode::GetCategory()const
{
	return Category::Type::Scene;
}

void SceneNode::UpdateThis(sf::Time)
{
}

void SceneNode::UpdateChildren(sf::Time dt)
{
	for (auto& child : m_Children)
		child->Update(dt);
}

void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	DrawThis(target, states);
	DrawChildren(target, states);
}

void SceneNode::DrawThis(sf::RenderTarget & target, sf::RenderStates states) const
{
}

void SceneNode::DrawChildren(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto& child : m_Children)
		child->draw(target, states);
}
