#pragma once
#include "pch.h"
#include <memory>
#include <vector>


class SceneNode : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
					SceneNode();
	
	void			AttachChild(Ptr child);
	Ptr				DetachChild(const SceneNode& node);
	
	void			Update(sf::Time);
	
	sf::Vector2f	GetWorldPosition();
	sf::Transform	GetWorldTransform();

	void			OnCommand(const Command& cmd, sf::Time dt);
	virtual unsigned int GetCategory()const;
private:
	virtual void UpdateThis(sf::Time);
	void UpdateChildren(sf::Time);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void DrawThis(sf::RenderTarget& target, sf::RenderStates states) const;
	void DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<std::unique_ptr<SceneNode>> m_Children;
	SceneNode* m_pParent;
};