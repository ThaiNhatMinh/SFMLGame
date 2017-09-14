#pragma once
#include "pch.h"

namespace GUI
{
	class Component : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
	{
	public:
		typedef std::shared_ptr<Component> Ptr;
	public:
		Component();
		virtual ~Component();

		virtual bool	IsSelectable() const = 0;
		bool			IsSelect()const;
		virtual void	Select();
		virtual void	DeSelect();
		virtual bool	IsActive()const;
		virtual void	Active();
		virtual void	DeActive();
		virtual void	HandleEvent(const sf::Event& ev) = 0;
	private:
		bool m_IsSelect;
		bool m_IsActive;
	};
}