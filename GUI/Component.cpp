#include "pch.h"
#include "Component.h"

GUI::Component::Component():m_IsActive(0),m_IsSelect(0)
{
}

GUI::Component::~Component()
{
}

bool GUI::Component::IsSelect() const
{
	return m_IsSelect;
}

void GUI::Component::Select()
{
	m_IsSelect = 1;
}

void GUI::Component::DeSelect()
{
	m_IsSelect = 0;
}

bool GUI::Component::IsActive() const
{
	return m_IsActive;
}

void GUI::Component::Active()
{
	m_IsActive = 1;
}

void GUI::Component::DeActive()
{
	m_IsActive = 0;
}
