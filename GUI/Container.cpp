#include "pch.h"
#include "Container.h"

GUI::Container::Container()
{
	m_SelectChild = -1;

}

GUI::Container::~Container()
{
}

void GUI::Container::Pack(Component::Ptr component)
{
	m_Children.push_back(component);

	if (!HasSelection() && component->IsSelectable())
		Select(m_Children.size() - 1);

}

bool GUI::Container::IsSelectable() const
{
	return false;
}

void GUI::Container::HandleEvent(const sf::Event & ev)
{
	if (HasSelection() && m_Children[m_SelectChild]->IsActive())
		m_Children[m_SelectChild]->HandleEvent(ev);
	else if (ev.type == sf::Event::KeyReleased)
	{
		if (ev.key.code == sf::Keyboard::Up || ev.key.code == sf::Keyboard::W)
			SelectPrevoius();
		else if (ev.key.code == sf::Keyboard::Down || ev.key.code == sf::Keyboard::S)
			SelectNext();
		else if (ev.key.code == sf::Keyboard::Return || ev.key.code == sf::Keyboard::Space)
		{
			if (HasSelection()) m_Children[m_SelectChild]->Active();
		}
	}
}

void GUI::Container::draw(sf::RenderTarget & rt, sf::RenderStates rs) const
{
	rs.transform *= getTransform();

	for (std::size_t i = 0; i < m_Children.size(); i++)
		rt.draw(*m_Children[i], rs);
}

bool GUI::Container::HasSelection()
{
	return m_SelectChild>=0;
}

void GUI::Container::Select(std::size_t pos)
{
	if (m_Children[pos]->IsSelectable())
	{
		if (HasSelection()) m_Children[m_SelectChild]->DeSelect();
		m_Children[pos]->Select();
		m_SelectChild = pos;
	}
}

void GUI::Container::SelectNext()
{
	if (!HasSelection()) return;
	// Search next component that is selectable
	int next = m_SelectChild;

	do next = (next + 1) % m_Children.size();
	while (!m_Children[next]->IsSelectable());

	Select(next);
}

void GUI::Container::SelectPrevoius()
{
	if (!HasSelection()) return;
	// Search previous component that is selectable
	int prev = m_SelectChild;
	do
		prev = (prev + m_Children.size() - 1) % m_Children.size();
	while (!m_Children[prev]->IsSelectable());
	// Select that component
	Select(prev);
}
