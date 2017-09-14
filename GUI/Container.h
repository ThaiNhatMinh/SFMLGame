#pragma once
#include "pch.h"


namespace GUI
{
	class Container : public Component
	{
		typedef std::shared_ptr<Container> Ptr;
	public:
		Container();
		~Container();

		void Pack(Component::Ptr component);
		virtual bool IsSelectable()const override;
		virtual void HandleEvent(const sf::Event& ev) override;

	protected:
		virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs)const override;
		bool HasSelection();
		void Select(std::size_t pos);
		void SelectNext();
		void SelectPrevoius();
	private:
		std::vector<Component::Ptr> m_Children;
		int m_SelectChild;
	};
}